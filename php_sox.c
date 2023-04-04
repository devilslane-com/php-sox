#include "php_sox.h"

typedef struct _php_sox_object {
    zend_object std;
    sox_format_t *input_file;
    sox_format_t *output_file;
} php_sox_object;

// Define a class entry for the Sox class
zend_class_entry *sox_ce;

/********************************************************************************************************************
  Declare all the methods
********************************************************************************************************************/
PHP_METHOD(Sox, __construct);
PHP_METHOD(Sox, analyze);
PHP_METHOD(Sox, bass);
PHP_METHOD(Sox, chorus);
PHP_METHOD(Sox, compressor);
PHP_METHOD(Sox, concatenate);
PHP_METHOD(Sox, convert);
PHP_METHOD(Sox, delay);
PHP_METHOD(Sox, dither);
PHP_METHOD(Sox, echo);
PHP_METHOD(Sox, eq);
PHP_METHOD(Sox, extract_left);
PHP_METHOD(Sox, extract_right);
PHP_METHOD(Sox, fade);
PHP_METHOD(Sox, filter);
PHP_METHOD(Sox, formats);
PHP_METHOD(Sox, gain);
PHP_METHOD(Sox, load);
PHP_METHOD(Sox, loudness);
PHP_METHOD(Sox, metadata);
PHP_METHOD(Sox, mix);
PHP_METHOD(Sox, noise);
PHP_METHOD(Sox, normalize);
PHP_METHOD(Sox, pad);
PHP_METHOD(Sox, phaser);
PHP_METHOD(Sox, pitch);
PHP_METHOD(Sox, repeat);
PHP_METHOD(Sox, reverb);
PHP_METHOD(Sox, reverse);
PHP_METHOD(Sox, sample_rate);
PHP_METHOD(Sox, sample_size);
PHP_METHOD(Sox, save);
PHP_METHOD(Sox, segment);
PHP_METHOD(Sox, speed);
PHP_METHOD(Sox, splice);
PHP_METHOD(Sox, stretch);
PHP_METHOD(Sox, swap);
PHP_METHOD(Sox, tempo);
PHP_METHOD(Sox, to_mono);
PHP_METHOD(Sox, to_stereo);
PHP_METHOD(Sox, treble);
PHP_METHOD(Sox, tremolo);
PHP_METHOD(Sox, trim);
PHP_METHOD(Sox, vad);
PHP_METHOD(Sox, version);
PHP_METHOD(Sox, visualize);
PHP_METHOD(Sox, volume);

/********************************************************************************************************************
  Define all arguments sent to individual methods
********************************************************************************************************************/
ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_convert, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, output_file_type, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_load, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, input_file_path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_sample_rate, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, new_sample_rate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_sample_size, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, new_sample_size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_save, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, output_file_path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_speed, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_visualize, 0, 0, 5)
    ZEND_ARG_TYPE_INFO(0, output_file_path, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, rgb, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_volume, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

/********************************************************************************************************************
  Define the class method list (class, method, args, access levels)
********************************************************************************************************************/
static const zend_function_entry sox_methods[] = {
    PHP_ME(Sox, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Sox, analyze, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, bass, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, chorus, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, compressor, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, concatenate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, convert, arginfo_sox_convert, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, delay, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, dither, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, echo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, eq, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, extract_left, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, extract_right, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, fade, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, filter, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, formats, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, gain, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, load, arginfo_sox_load, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, loudness, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, metadata, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, mix, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, noise, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, normalize, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, pad, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, phaser, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, pitch, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, repeat, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, reverb, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, reverse, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, sample_rate, arginfo_sox_sample_rate, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, sample_size, arginfo_sox_sample_size, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, save, arginfo_sox_save, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, segment, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, speed, arginfo_sox_speed, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, splice, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, stretch, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, swap, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, tempo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, to_mono, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, to_stereo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, treble, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, tremolo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, trim, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, vad, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, version, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, visualize, arginfo_sox_visualize, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, volume, arginfo_sox_volume, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

// Module entry
zend_module_entry sox_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_SOX_EXTNAME,
    NULL,                  /* Functions */
    PHP_MINIT(sox),        /* MINIT */
    NULL,                  /* MSHUTDOWN */
    NULL,                  /* RINIT */
    NULL,                  /* RSHUTDOWN */
    NULL,                  /* MINFO */
    PHP_SOX_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// Implement the entry point symbol
ZEND_GET_MODULE(sox)

// Initialize the module
PHP_MINIT_FUNCTION(sox)
{
    // Initialize the Sox class
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Sox", sox_methods);
    sox_ce = zend_register_internal_class(&ce TSRMLS_CC);

    return SUCCESS;
}

/********************************************************************************************************************
  CONSTRUCTOR
********************************************************************************************************************/
PHP_METHOD(Sox, __construct)
{
    // Initialize the SoX library
    if (sox_init() != SOX_SUCCESS) {
        zend_throw_exception(zend_ce_exception, "Failed to initialize SoX library", 0 TSRMLS_CC);
        return;
    }
}

/********************************************************************************************************************
  ANALYZE
********************************************************************************************************************/
PHP_METHOD(Sox, analyze)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before analyze().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("stat"));
    sox_effect_options(effect, 0, NULL);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    // Cleanup
    sox_delete_effects_chain(chain);
}

/********************************************************************************************************************
  CONVERT (string $format = 'mp3') 
********************************************************************************************************************/
PHP_METHOD(Sox, convert)
{
    char *output_file_type;
    size_t output_file_type_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
                              &output_file_type, &output_file_type_len) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before convert().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char output_file_path[obj->input_file->filename.len + output_file_type_len + 2];
    snprintf(output_file_path, sizeof(output_file_path), "%s.%s", obj->input_file->filename.buf, output_file_type);

    sox_format_t *output_file = sox_open_write(output_file_path, &obj->input_file->signal, &obj->input_file->encoding, output_file_type, NULL, NULL);
    if (!output_file) {
        zend_throw_exception(zend_ce_exception, "Failed to open output file for writing.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &output_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("output"));
    sox_effect_options(effect, 0, NULL);
    sox_add_effect(chain, effect, &obj->input_file->signal, &output_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    sox_delete_effects_chain(chain);
    sox_close(output_file);
}

/********************************************************************************************************************
  FORMATS 
********************************************************************************************************************/
PHP_METHOD(Sox, formats)
{
    sox_format_tab_t const *formats = sox_get_format_fns();
    array_init(return_value);

    while (formats->fn) {
        sox_format_fns_info_t format_info;
        sox_format_info(formats, &format_info);

        zval format_array;
        array_init(&format_array);

        add_assoc_string(&format_array, "name", format_info.name);
        add_assoc_string(&format_array, "description", format_info.description);
        add_assoc_string(&format_array, "flags", format_info.flags);
        
        add_next_index_zval(return_value, &format_array);

        ++formats;
    }
}

/********************************************************************************************************************
  LOAD (string $path_to_file)
********************************************************************************************************************/
PHP_METHOD(Sox, load)
{
    char *input_file_path;
    size_t input_file_path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
                              &input_file_path, &input_file_path_len) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());
    obj->input_file = sox_open_read(input_file_path, NULL, NULL, NULL);

    if (!obj->input_file) {
        sox_quit();
        zend_throw_exception(zend_ce_exception, "Failed to open input file", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

/********************************************************************************************************************
  SAMPLE_RATE (int $rate_in_HZ = 48000)
********************************************************************************************************************/
PHP_METHOD(Sox, sample_rate)
{
    zend_long new_sample_rate;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",
                              &new_sample_rate) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before change_sample_rate().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    obj->input_file->signal.rate = new_sample_rate;
}

/********************************************************************************************************************
  SAMPLE_SIZE (int $size_in_bits = 16)
********************************************************************************************************************/
PHP_METHOD(Sox, sample_size)
{
    zend_long new_sample_size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",
                              &new_sample_size) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before change_sample_size().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    obj->input_file->encoding.bits_per_sample = new_sample_size;
}

/********************************************************************************************************************
  SAVE (string $path_to_save_to)
********************************************************************************************************************/
PHP_METHOD(Sox, save)
{
    char *output_file_path;
    size_t output_file_path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
                              &output_file_path, &output_file_path_len) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    // Open the output file
    obj->output_file = sox_open_write(output_file_path, &obj->input_file->signal,
                                      &obj->input_file->encoding, NULL, NULL, NULL);

    if (!obj->output_file) {
        sox_quit();
        zend_throw_exception(zend_ce_exception, "Failed to open output file", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    // Create and configure the effects chain
    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->output_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("input"));
    char *args[] = {(char *)obj->input_file};
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->output_file->signal);

    effect = sox_create_effect(sox_find_effect("output"));
    args[0] = (char *)obj->output_file;
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->output_file->signal);

    // Process the audio and save to the output file
    sox_flow_effects(chain, NULL, NULL);

    // Cleanup
    sox_delete_effects_chain(chain);
    sox_close(obj->output_file);
    sox_close(obj->input_file);
    sox_quit();

    RETURN_TRUE;
}

/********************************************************************************************************************
  SPEED (float $factor = 1.0)
********************************************************************************************************************/
PHP_METHOD(Sox, speed)
{
    double factor;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &factor) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());
    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("speed"));
    char factor_str[16];
    snprintf(factor_str, sizeof(factor_str), "%.2f", factor);
    char *args[] = {factor_str};
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    // Cleanup
    sox_delete_effects_chain(chain);

    RETURN_TRUE;
}


/********************************************************************************************************************
  VERSION
********************************************************************************************************************/
PHP_METHOD(Sox, version)
{
    const char *version = sox_version_info();
    RETURN_STRING(version);
}

/********************************************************************************************************************
  VISUALIZE (string $path_to_image_export, int $image_width, int $image_height, array $rgb_values = [0, 0, 0])
********************************************************************************************************************/
PHP_METHOD(Sox, visualize)
{
    char *output_file_path;
    size_t output_file_path_len;
    zend_long width, height;
    zval *rgb_array;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sllA",
                              &output_file_path, &output_file_path_len,
                              &width, &height, &rgb_array) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before visualize().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    // Extract the RGB color values from the array
    HashTable *rgb_hash = Z_ARRVAL_P(rgb_array);
    zval *r, *g, *b;

    r = zend_hash_index_find(rgb_hash, 0);
    g = zend_hash_index_find(rgb_hash, 1);
    b = zend_hash_index_find(rgb_hash, 2);

    if (!r || !g || !b) {
        zend_throw_exception(zend_ce_exception, "Invalid RGB array. It must contain 3 integer values.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    // Construct the command line arguments for the spectrogram effect
    char width_str[16], height_str[16], r_str[16], g_str[16], b_str[16];
    snprintf(width_str, sizeof(width_str), "%ld", width);
    snprintf(height_str, sizeof(height_str), "%ld", height);
    snprintf(r_str, sizeof(r_str), "%ld", Z_LVAL_P(r));
    snprintf(g_str, sizeof(g_str), "%ld", Z_LVAL_P(g));
    snprintf(b_str, sizeof(b_str), "%ld", Z_LVAL_P(b));

    char *args[] = {"-o", output_file_path, "-w", width_str, "-h", height_str, "-r", r_str, "-g", g_str, "-b", b_str};

    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("spectrogram"));
    sox_effect_options(effect, sizeof(args) / sizeof(args[0]), args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    // Cleanup
    sox_delete_effects_chain(chain);
}

/********************************************************************************************************************
  VOLUME (float $factor = 1.0)
********************************************************************************************************************/
PHP_METHOD(Sox, volume)
{
    double factor;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &factor) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());
    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("vol"));
    char factor_str[16];
    snprintf(factor_str, sizeof(factor_str), "%.2f", factor);
    char *args[] = {factor_str};
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    // Cleanup
    sox_delete_effects_chain(chain);

    RETURN_TRUE;
}

/********************************************************************************************************************
  OUTPUT HANDLERS
********************************************************************************************************************/

// Custom output handler for stat effect
static int stat_output_handler(sox_bool all_done, void *client_data)
{
    zval *return_array = (zval *)client_data;

    if (!all_done) {
        char buffer[1024];
        fgets(buffer, sizeof(buffer), stdin);

        if (feof(stdin) || ferror(stdin)) {
            return SOX_EOF;
        }

        char key[128];
        double value;

        if (sscanf(buffer, "%127[^:]:%lf", key, &value) == 2) {
            add_assoc_double(return_array, key, value);
        }
    }

    return SOX_SUCCESS;
}