#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

#define BUILD_FOLDER "./build/"
#define RESULTS_FOLDER "./results/"

// How many times to run a single build with the same parameters to compute an
// average duration.
#define SAMPLES_COUNT 10
// How many jobs a single build should create. Set it to something like twice
// the amount of cores you have for a good measure, I dunno.
#define WORKERS_COUNT 32

typedef struct {
    double *items;
    size_t count;
    size_t capacity;
} Samples;

static Cmd cmd = {0};
static Procs procs = {0};
static Samples samples = {0};
static size_t jobs_counter = 0;
static size_t jobs_max = 0;
static const char *workers[] = { "sleeper", "looper" };

typedef struct {
    const char *worker_type;
    size_t worker_count;
    size_t max_procs;
    Nob_Async_Eviction_Strat strategy;
} Config;

bool single_build(Config config)
{
    const char *worker_type = config.worker_type;
    size_t worker_count = config.worker_count;
    size_t max_procs = config.max_procs;

    for (size_t i = 0; i < worker_count; ++i) {
        cmd_append(&cmd, temp_sprintf(BUILD_FOLDER"%s", worker_type));
        if (!cmd_run(&cmd, .async = &procs, .max_procs = max_procs, .evict = config.strategy)) return false;
        jobs_counter += 1;
        size_t bar_max = 20;
        size_t bar_current = bar_max*jobs_counter/jobs_max;
        const char *spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
        printf("\rProgress: ");
        for (size_t j = 0;           j < bar_current; ++j) printf("#");
        for (size_t j = bar_current; j < bar_max;     ++j) printf(".");
        printf(" %s Jobs: %zu/%zu, max_procs=%zu", spinner[jobs_counter%ARRAY_LEN(spinner)], jobs_counter, jobs_max, max_procs);
        fflush(stdout);
    }

    if (!nob_procs_wait(procs)) return false;
    procs.count = 0;

    return true;
}

bool average_time_of_several_builds(Config config, double *avg)
{
    for (size_t i = 0; i < SAMPLES_COUNT; ++i) {
        uint64_t begin = nanos_since_unspecified_epoch();
        if (!single_build(config)) return false;
        da_append(&samples, (double)(nanos_since_unspecified_epoch() - begin)/NANOS_PER_SEC);
    }

    assert(samples.count > 0);
    double sum = 0.0f;
    da_foreach(double, sample, &samples) sum += *sample;
    *avg = sum/samples.count;
    samples.count = 0;

    return true;
}

bool build_exec(const char *input_path, const char *output_path)
{
    nob_cc(&cmd);
    nob_cc_flags(&cmd);
    nob_cc_output(&cmd, output_path);
    nob_cc_inputs(&cmd, input_path);
    return cmd_run(&cmd);
}

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF_PLUS(argc, argv, "./nob.h");

    srand(time(0));

    if (!mkdir_if_not_exists(RESULTS_FOLDER)) return 1;
    if (!mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    for (size_t i = 0; i < ARRAY_LEN(workers); ++i) {
        const char *input_path = temp_sprintf("%s.c", workers[i]);
        const char *output_path = temp_sprintf(BUILD_FOLDER"%s", workers[i]);
        if (!build_exec(input_path, output_path)) return 1;
    }

    Samples avgs = {0};
    String_Builder sb = {0};

    Config config = {
        .worker_count = WORKERS_COUNT,
    };
    size_t start_max_procs = 1;

    for (size_t i = 0; i < ARRAY_LEN(workers); ++i) {
        for (size_t strategy = 0; strategy < COUNT_STARTS; ++strategy) {
            size_t mark = temp_save();
            avgs.count = 0;

            config.worker_type = workers[i];
            config.strategy = strategy;

            printf("strategy        = %s\n",  nob_eviction_strat_name(config.strategy));
            printf("worker_type     = %s\n",  config.worker_type);
            printf("start_max_procs = %zu\n", start_max_procs);
            printf("worker_count    = %zu\n", config.worker_count);
            printf("samples_count   = %d\n",  SAMPLES_COUNT);

            jobs_counter = 0;
            jobs_max = (config.worker_count - start_max_procs + 1)*SAMPLES_COUNT*config.worker_count;

            nob_minimal_log_level = WARNING;
            for (
                config.max_procs = start_max_procs;
                config.max_procs <= config.worker_count;
                ++config.max_procs
            ) {
                double avg = 0.0f;
                if (!average_time_of_several_builds(config, &avg)) return 1;
                da_append(&avgs, avg);
            }
            printf("\n"); // Break the progress reporting
            nob_minimal_log_level = INFO;

            sb.count = 0;
            sb_appendf(&sb, "max_procs,avg_secs\n");
            for (size_t i = 0; i < avgs.count; ++i) {
                sb_appendf(&sb, "%zu,%lf\n", i + start_max_procs, avgs.items[i]);
            }

            nob_log(INFO, "Results:");
            printf("%.*s", (int)sb.count, sb.items);

            const char *result_path = temp_sprintf(RESULTS_FOLDER"result-%s%zu-%zu-%s.csv", config.worker_type, start_max_procs, config.worker_count, nob_eviction_strat_name(config.strategy));
            if (!write_entire_file(result_path, sb.items, sb.count)) return 1;
            nob_log(INFO, "Generated %s", result_path);

            temp_rewind(mark);
        }
    }

    return 0;
}
