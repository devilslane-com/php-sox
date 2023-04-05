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
ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_bass, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, decibels, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, frequency, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_chorus, 0)
    ZEND_ARG_TYPE_INFO(0, gain_in, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, gain_out, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, delay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, decay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, speed, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, depth, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_concatenate, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, files, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_convert, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, bitrate, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, output_file_type, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_echo, 0)
    ZEND_ARG_TYPE_INFO(0, gain_in, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, gain_out, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, delay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, decay, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_eq, 0)
    ZEND_ARG_TYPE_INFO(0, frequency, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, gain, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_fade, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, type, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, length, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_filter, 0, 0, 3)
    ZEND_ARG_TYPE_INFO(0, filter_type, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, frequency, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_flanger, 0)
    ZEND_ARG_TYPE_INFO(0, delay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, depth, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, regen, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, speed, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, shape, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, phase, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, interpolation, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_gain, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, decibels, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_load, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, input_file_path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_loudness, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, gain, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, reference, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_metadata, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, metadata, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_mix, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, input_array, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_noise, 0, 0, 3)
    ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, duration, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, sensitivity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_normalize, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, decibels, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_pad, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, end, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_phaser, 0)
    ZEND_ARG_TYPE_INFO(0, gain_in, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, gain_out, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, delay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, decay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, speed, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_pitch, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, hertz, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_repeat, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_reverb, 0)
    ZEND_ARG_TYPE_INFO(0, reverberance, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, hf_damping, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, room_scale, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, stereo_depth, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, pre_delay, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, wet_gain, IS_DOUBLE, 0)
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

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_segment, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, duration, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_speed, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_splice, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, position, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_stretch, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_tempo, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_treble, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, decibels, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, frequency, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_sox_tremolo, 0)
    ZEND_ARG_TYPE_INFO(0, speed, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, depth, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_trim, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, duration, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_sox_vad, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, initial_trim, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, trigger_level, IS_DOUBLE, 0)
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
    PHP_ME(Sox, bass, arginfo_sox_bass, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, chorus, arginfo_sox_chorus, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, compressor, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, concatenate, arginfo_sox_concatenate, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, convert, arginfo_sox_convert, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, delay, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, dither, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, echo, arginfo_sox_echo, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, eq, arginfo_sox_eq, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, extract_left, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, extract_right, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, fade, arginfo_sox_fade, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, filter, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, formats, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, gain, arginfo_sox_gain, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, load, arginfo_sox_load, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, loudness, arginfo_sox_loudness, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, metadata, arginfo_sox_metadata, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, mix, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, noise, arginfo_sox_noise, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, normalize, arginfo_sox_normalize, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, pad, arginfo_sox_pad, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, phaser, arginfo_sox_phaser, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, pitch, arginfo_sox_pitch, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, repeat, arginfo_sox_repeat, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, reverb, arginfo_sox_reverb, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, reverse, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, sample_rate, arginfo_sox_sample_rate, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, sample_size, arginfo_sox_sample_size, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, save, arginfo_sox_save, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, segment, arginfo_sox_segment, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, speed, arginfo_sox_speed, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, splice, arginfo_sox_splice, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, stretch, arginfo_sox_stretch, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, swap, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, tempo, arginfo_sox_tempo, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, to_mono, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, to_stereo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, treble, arginfo_sox_treble, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, tremolo, arginfo_sox_tremolo, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, trim, arginfo_sox_trim, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, vad, arginfo_sox_vad, ZEND_ACC_PUBLIC)
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
  BASS (float $decibels = 1.0, float $frequency = 400, float $width = 100) 
********************************************************************************************************************/
PHP_METHOD(Sox, bass)
{
    double gain_db, freq, width;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &gain_db, &freq, &width) == FAILURE) {
        RETURN_NULL();
    }

    php_sox_object *intern = Z_SOX_P(getThis());
    sox_effects_chain_t *chain = intern->chain;
    sox_effect_t *effect = sox_create_effect(sox_find_effect("bass"));

    char gain_str[20], freq_str[20], width_str[20];
    snprintf(gain_str, sizeof(gain_str), "%.2f", gain_db);
    snprintf(freq_str, sizeof(freq_str), "%.0f", freq);
    snprintf(width_str, sizeof(width_str), "%.0f", width);

    char *argv[] = { "bass", gain_str, freq_str, width_str };
    sox_effect_options(effect, 4, argv);
    chain_add_effect(chain, effect);
}

/********************************************************************************************************************
  CHORUS (float $gain_in = 1.0, float $gain_out = 0, float $delay = 0, float $decay = 0, float $speed = 0, float $depth) 
********************************************************************************************************************/
PHP_METHOD(Sox, chorus)
{
    double gain_in, gain_out, delay, decay, speed, depth;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_DOUBLE(gain_in)
        Z_PARAM_DOUBLE(gain_out)
        Z_PARAM_DOUBLE(delay)
        Z_PARAM_DOUBLE(decay)
        Z_PARAM_DOUBLE(speed)
        Z_PARAM_DOUBLE(depth)
    ZEND_PARSE_PARAMETERS_END();

    apply_chorus_effect(getThis(), gain_in, gain_out, delay, decay, speed, depth);
}

/********************************************************************************************************************
  CONCATENATE (array $files = ['audio1.wav', 'audio2.wav']) 
********************************************************************************************************************/
PHP_METHOD(Sox, concatenate)
{
    zval *files_array;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &files_array) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (obj->input_file) {
        sox_close(obj->input_file);
    }

    char tmp_template[] = "/tmp/sox_temp_XXXXXX";
    int tmp_fd = mkstemp(tmp_template);

    if (tmp_fd == -1) {
        zend_throw_exception(zend_ce_exception, "Failed to create temporary file.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    close(tmp_fd);

    sox_format_t *output = sox_open_write(tmp_template, NULL, NULL, NULL);

    if (!output) {
        zend_throw_exception(zend_ce_exception, "Failed to open output file.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    HashTable *files_table = Z_ARRVAL_P(files_array);
    zval *file;
    ZEND_HASH_FOREACH_VAL(files_table, file)
    {
        if (Z_TYPE_P(file) != IS_STRING) {
            zend_throw_exception(zend_ce_exception, "All elements in the input array must be file paths (strings).", 0 TSRMLS_CC);
            sox_close(output);
            RETURN_FALSE;
        }

        sox_format_t *input = sox_open_read(Z_STRVAL_P(file), NULL, NULL, NULL);

        if (!input) {
            zend_throw_exception_ex(zend_ce_exception, 0 TSRMLS_CC, "Failed to open input file: %s", Z_STRVAL_P(file));
            sox_close(output);
            RETURN_FALSE;
        }

        sox_effects_chain_t *chain = sox_create_effects_chain(&sox_globals.input_encoding, &output->encoding);
        sox_effect_t *effect = sox_create_effect(sox_find_effect("input"));
        sox_effect_options(effect, 1, (char **)&input);
        sox_add_effect(chain, effect, &input->signal, &input->signal);

        effect = sox_create_effect(sox_find_effect("output"));
        sox_effect_options(effect, 1, (char **)&output);
        sox_add_effect(chain, effect, &input->signal, &output->signal);

        sox_flow_effects(chain, NULL, NULL);
        sox_delete_effects_chain(chain);
        sox_close(input);
    }
    ZEND_HASH_FOREACH_END();

    sox_close(output);

    obj->input_file = sox_open_read(tmp_template, NULL, NULL, NULL);

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "Failed to open temporary file.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    unlink(tmp_template);
}

/********************************************************************************************************************
  CONVERT (int $bitrate = 256, string $format = 'mp3') 
********************************************************************************************************************/
PHP_METHOD(Sox, convert)
{
    char *output_file_type;
    size_t output_file_type_len;
    zend_long bitrate;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",
                              &output_file_type, &output_file_type_len,
                              &bitrate) == FAILURE) {
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
    output_file->encoding.compression = bitrate / 1000.0;

    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &output_file->encoding);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("output"));
    sox_effect_options(effect, 0, NULL);
    sox_add_effect(chain, effect, &obj->input_file->signal, &output_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    sox_delete_effects_chain(chain);
    sox_close(output_file);
}

/********************************************************************************************************************
  DITHER
********************************************************************************************************************/
PHP_METHOD(Sox, dither)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *eff = sox_create_effect(sox_find_effect("dither"));
    sox_effect_options(eff, 0, NULL);
    chain_add_effect(obj, eff);
}

/********************************************************************************************************************
  ECHO (float $gain_in = 0, float $gain_out = 0, float $delay = 0, float $decay = 0)
********************************************************************************************************************/
PHP_METHOD(Sox, echo)
{
    double gain_in, gain_out, delay, decay;

    ZEND_PARSE_PARAMETERS_START(4, 4)
        Z_PARAM_DOUBLE(gain_in)
        Z_PARAM_DOUBLE(gain_out)
        Z_PARAM_DOUBLE(delay)
        Z_PARAM_DOUBLE(decay)
    ZEND_PARSE_PARAMETERS_END();

    apply_echo_effect(getThis(), gain_in, gain_out, delay, decay);
}

/********************************************************************************************************************
  EQ (float $frequency_hz = 1500, float $width_hz = 100, float $decibels = 3.5)
********************************************************************************************************************/
PHP_METHOD(Sox, eq)
{
    double frequency, width, gain;

    ZEND_PARSE_PARAMETERS_START(3, 3)
        Z_PARAM_DOUBLE(frequency)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(gain)
    ZEND_PARSE_PARAMETERS_END();

    apply_equalizer_effect(getThis(), frequency, width, gain);
}

/********************************************************************************************************************
  EXTRACT_LEFT 
********************************************************************************************************************/
PHP_METHOD(Sox, extract_left)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before extract_left().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("remix"));
    char *opts[] = {"1"};
    sox_effect_options(effect, 1, opts);
    apply_effect_to_input_file(obj, effect);
}

/********************************************************************************************************************
  EXTRACT_RIGHT
********************************************************************************************************************/
PHP_METHOD(Sox, extract_right)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before extract_right().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("remix"));
    char *opts[] = {"2"};
    sox_effect_options(effect, 1, opts);
    apply_effect_to_input_file(obj, effect);
}

/********************************************************************************************************************
  FADE (string $type = "in|out", int $length = 10) 
********************************************************************************************************************/
PHP_METHOD(Sox, fade)
{
    char *type;
    size_t type_len;
    double length;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(type, type_len)
        Z_PARAM_DOUBLE(length)
    ZEND_PARSE_PARAMETERS_END();

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    if (strcmp(type, "in") != 0 && strcmp(type, "out") != 0) {
        zend_throw_exception(zend_ce_exception, "Invalid fade type. Use 'in' or 'out'.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *eff = sox_create_effect(sox_find_effect("fade"));

    char length_str[50];
    snprintf(length_str, sizeof(length_str), "%lf", length);
    char *argv[] = {type, length_str};
    sox_effect_options(eff, 2, argv);
    chain_add_effect(obj, eff);
}

/********************************************************************************************************************
  FLANGER (float $delay_ms = 0, float $depth_ms = 0, float $regeneration_percent = 0, float $width_percent = 0, float $speed_hz = 0, string $shape = "sine|triangle", string $phase_percent, string $interpolation ="linear|quadratic")
********************************************************************************************************************/
PHP_METHOD(Sox, flanger)
{
    double delay, depth, regen, width, speed;
    char *shape, *phase, *interpolation;

    ZEND_PARSE_PARAMETERS_START(8, 8)
        Z_PARAM_DOUBLE(delay)
        Z_PARAM_DOUBLE(depth)
        Z_PARAM_DOUBLE(regen)
        Z_PARAM_DOUBLE(width)
        Z_PARAM_DOUBLE(speed)
        Z_PARAM_STRING(shape)
        Z_PARAM_STRING(phase)
        Z_PARAM_STRING(interpolation)
    ZEND_PARSE_PARAMETERS_END();

    apply_flanger_effect(getThis(), delay, depth, regen, width, speed, shape, phase, interpolation);
}

/********************************************************************************************************************
  FILTER (string $type = "allpass|bandpass|bankreject|lowpass|highpass", float $frequency_hz = 1000, float $width_hz = 100)
********************************************************************************************************************/
PHP_METHOD(Sox, filter) 
{
    char *filter_type;
    double frequency, width;
    size_t filter_type_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sdd", &filter_type, &filter_type_len, &frequency, &width) == FAILURE) {
        RETURN_NULL();
    }

    php_sox_object *intern = Z_SOX_P(getThis());
    sox_effects_chain_t *chain = intern->chain;
    sox_effect_t *effect = sox_create_effect(sox_find_effect(filter_type));

    char frequency_str[20], width_str[20];
    snprintf(frequency_str, sizeof(frequency_str), "%.2f", frequency);
    snprintf(width_str, sizeof(width_str), "%.2f", width);

    char *argv[] = { filter_type, frequency_str, width_str };
    sox_effect_options(effect, 3, argv);
    chain_add_effect(chain, effect);
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
  GAIN (float $decibels = 1.0) 
********************************************************************************************************************/
PHP_METHOD(Sox, gain)
{
    double decibels;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &decibels) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before gain().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("gain"));
    double opts[] = {decibels};
    sox_effect_options(effect, 1, (char **)&opts);
    apply_effect_to_input_file(obj, effect);
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
  LOUDNESS (float $gain = 1.0, float $reference = 0.5)
********************************************************************************************************************/
PHP_METHOD(Sox, loudness)
{
    double gain, reference;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &gain, &reference) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before loudness().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("loudness"));
    double opts[] = {gain, reference};
    sox_effect_options(effect, 2, (char **)&opts);
    apply_effect_to_input_file(obj, effect);
}

PHP_METHOD(Sox, metadata)
{
    zval *metadata;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &metadata) == FAILURE) {
        RETURN_FALSE;
    }
    
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    HashTable *metadata_hash = Z_ARRVAL_P(metadata);
    zval *value;
    zend_string *key;

    ZEND_HASH_FOREACH_STR_KEY_VAL(metadata_hash, key, value)
    {
        if (key) {
            sox_set_comment(obj->input_file->oob.comments, ZSTR_VAL(key), Z_STRVAL_P(value));
        }
    }
    ZEND_HASH_FOREACH_END();
}

/********************************************************************************************************************
  MIX (array $files = ['audio1.wav', 'audio2.wav'])
********************************************************************************************************************/
PHP_METHOD(Sox, mix) 
{
    zval *input_array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &input_array) == FAILURE) {
        RETURN_NULL();
    }

    php_sox_object *intern = Z_SOX_P(getThis());
    sox_format_t *combined = sox_open_memstream_write(&intern->buffer, &intern->buffer_size, &intern->signal_info, &intern->encoding_info, intern->filetype, NULL);

    sox_mix_params_t mix_params;
    mix_params.weights_type = sox_mix_weights_none;
    sox_mix(&combined, 1, (char **)&input_array, &mix_params);

    intern->output = combined;
}

/********************************************************************************************************************
  NOISE (int $start_ms, int $duration_ms, float $sensitivity)
********************************************************************************************************************/
PHP_METHOD(Sox, noise)
{
    long start, duration;
    double sensitivity;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lld", &start, &duration, &sensitivity) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    // Trim the audio and create a temporary noise profile
    char tmp_profile_template[] = "/tmp/sox_noise_profile_XXXXXX";
    int tmp_profile_fd = mkstemp(tmp_profile_template);

    if (tmp_profile_fd == -1) {
        zend_throw_exception(zend_ce_exception, "Failed to create temporary noise profile file.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    close(tmp_profile_fd);

    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);
    sox_effect_t *effect = sox_create_effect(sox_find_effect("trim"));
    char *start_str;
    char *duration_str;
    asprintf(&start_str, "%ld", start);
    asprintf(&duration_str, "%ld", duration);
    char *trim_args[] = {start_str, duration_str};
    sox_effect_options(effect, 2, trim_args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);
    free(start_str);
    free(duration_str);

    effect = sox_create_effect(sox_find_effect("noiseprof"));
    sox_effect_options(effect, 1, &tmp_profile_template);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);

    sox_flow_effects(chain, NULL, NULL);
    sox_delete_effects_chain(chain);

    // Apply noisered effect using the temporary noise profile
    chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);
    effect = sox_create_effect(sox_find_effect("noisered"));
    char sensitivity_str[32];
    snprintf(sensitivity_str, sizeof(sensitivity_str), "%f", sensitivity);
    char *noisered_args[] = {tmp_profile_template, sensitivity_str};
    sox_effect_options(effect, 2, noisered_args);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);

    sox_flow_effects(chain, NULL, NULL);
    sox_delete_effects_chain(chain);

    // Clean up temporary noise profile
    unlink(tmp_profile_template);
}

/********************************************************************************************************************
  NORMALIZE
********************************************************************************************************************/
PHP_METHOD(Sox, normalize)
{
    double decibels;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(decibels)
    ZEND_PARSE_PARAMETERS_END();

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *eff = sox_create_effect(sox_find_effect("norm"));

    char decibels_str[50];
    snprintf(decibels_str, sizeof(decibels_str), "%lf", decibels);
    char *argv[] = {decibels_str};
    sox_effect_options(eff, 1, argv);
    chain_add_effect(obj, eff);
}

/********************************************************************************************************************
  PAD (float $start = 0, float $end = 400)
********************************************************************************************************************/
PHP_METHOD(Sox, pad)
{
    long start, end;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &start, &end) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char *start_str;
    char *end_str;
    asprintf(&start_str, "%ld", start);
    asprintf(&end_str, "%ld", end);
    char *pad_args[] = {start_str, end_str};
    apply_single_effect(obj, "pad", 2, pad_args TSRMLS_CC);
    free(start_str);
    free(end_str);
}

/********************************************************************************************************************
  PHASER (float $gain_in = 0, float $gain_out = 0, float $delay_ms = 0, float $decay_ms = 0, float $speed_ms = 0)
********************************************************************************************************************/
PHP_METHOD(Sox, phaser)
{
    double gain_in, gain_out, delay, decay, speed;

    ZEND_PARSE_PARAMETERS_START(5, 5)
        Z_PARAM_DOUBLE(gain_in)
        Z_PARAM_DOUBLE(gain_out)
        Z_PARAM_DOUBLE(delay)
        Z_PARAM_DOUBLE(decay)
        Z_PARAM_DOUBLE(speed)
    ZEND_PARSE_PARAMETERS_END();

    apply_phaser_effect(getThis(), gain_in, gain_out, delay, decay, speed);
}

/********************************************************************************************************************
  PITCH (float $frequency_hertz = -31)
********************************************************************************************************************/
PHP_METHOD(Sox, pitch)
{
    double hertz;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &hertz) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    double cents = 1200.0 * log2(hertz / obj->input_file->signal.rate);
    char cents_str[32];
    snprintf(cents_str, sizeof(cents_str), "%f", cents);
    char *pitch_args[] = {cents_str};
    apply_single_effect(obj, "pitch", 1, pitch_args TSRMLS_CC);
}

/********************************************************************************************************************
  REPEAT (int $count = 5)
********************************************************************************************************************/
PHP_METHOD(Sox, repeat)
{
    long count;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &count) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char count_str[32];
    snprintf(count_str, sizeof(count_str), "%ld", count);
    char *repeat_args[] = {count_str};
    apply_single_effect(obj, "repeat", 1, repeat_args TSRMLS_CC);
}

/********************************************************************************************************************
  REVERB (float $reverberance_percent = 100, float $hf_damping_percent = 100, float $room_scale_percent = 100, float $stereo_depth_percent = 100, float $pre_delay_ms, float $wet_gain_decibels)
********************************************************************************************************************/
PHP_METHOD(Sox, reverb)
{
    double reverberance, hf_damping, room_scale, stereo_depth, pre_delay, wet_gain;

    ZEND_PARSE_PARAMETERS_START(6, 6)
        Z_PARAM_DOUBLE(reverberance)
        Z_PARAM_DOUBLE(hf_damping)
        Z_PARAM_DOUBLE(room_scale)
        Z_PARAM_DOUBLE(stereo_depth)
        Z_PARAM_DOUBLE(pre_delay)
        Z_PARAM_DOUBLE(wet_gain)
    ZEND_PARSE_PARAMETERS_END();

    apply_reverb_effect(getThis(), reverberance, hf_damping, room_scale, stereo_depth, pre_delay, wet_gain);
}

/********************************************************************************************************************
  REVERSE
********************************************************************************************************************/
PHP_METHOD(Sox, reverse)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before reverse().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("reverse"));
    sox_effect_options(effect, 0, NULL);
    apply_effect_to_input_file(obj, effect);
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
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before sample_rate().", 0 TSRMLS_CC);
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
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before sample_size().", 0 TSRMLS_CC);
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
  SEGMENT (float $start = 0, float $duration = 10)
********************************************************************************************************************/
PHP_METHOD(Sox, segment)
{
    long start, duration;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &start, &duration) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char *start_str;
    char *duration_str;
    asprintf(&start_str, "%ld", start);
    asprintf(&duration_str, "%ld", duration);
    char *trim_args[] = {start_str, duration_str};
    apply_single_effect(obj, "trim", 2, trim_args TSRMLS_CC);
    free(start_str);
    free(duration_str);
}

/********************************************************************************************************************
  SPLICE (float $position = 20)
********************************************************************************************************************/
PHP_METHOD(Sox, splice)
{
    long position;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &position) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char *position_str;
    asprintf(&position_str, "%ld", position);
    char *splice_args [] = {position_str};
    apply_single_effect(obj, "splice", 1, splice_args TSRMLS_CC);
    free(position_str);
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
  STRETCH (float $factor = 1.0)
********************************************************************************************************************/
PHP_METHOD(Sox, stretch)
{
    double factor;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &factor) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char factor_str[32];
    snprintf(factor_str, sizeof(factor_str), "%f", factor);
    char *stretch_args[] = {factor_str};
    apply_single_effect(obj, "stretch", 1, stretch_args TSRMLS_CC);
}

/********************************************************************************************************************
  SWAP
********************************************************************************************************************/
PHP_METHOD(Sox, swap)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    apply_single_effect(obj, "swap", 0, NULL TSRMLS_CC);
}

/********************************************************************************************************************
  TEMPO (float $factor = 1.0)
********************************************************************************************************************/
PHP_METHOD(Sox, tempo)
{
    double factor;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &factor) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char factor_str[32];
    snprintf(factor_str, sizeof(factor_str), "%f", factor);
    char *tempo_args[] = {factor_str};
    apply_single_effect(obj, "tempo", 1, tempo_args TSRMLS_CC);
}

/********************************************************************************************************************
  TO_MONO
********************************************************************************************************************/
PHP_METHOD(Sox, to_mono)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before to_mono().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("channels"));
    int opts[] = {1};
    sox_effect_options(effect, 1, (char **)&opts);
    apply_effect_to_input_file(obj, effect);
}

/********************************************************************************************************************
  TO_STEREO
********************************************************************************************************************/
PHP_METHOD(Sox, to_stereo)
{
    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No input file loaded. Call load() before to_stereo().", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    if (obj->input_file->signal.channels == 2) {
        zend_throw_exception(zend_ce_exception, "The input file is already stereo.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("channels"));
    int opts[] = {2};
    sox_effect_options(effect, 1, (char **)&opts);
    apply_effect_to_input_file(obj, effect);
}

/********************************************************************************************************************
  TREBLE (float $decibels = 1.0, float $frequency = 3500, float $width = 100) 
********************************************************************************************************************/
PHP_METHOD(Sox, treble)
{
    double gain_db, freq, width;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &gain_db, &freq, &width) == FAILURE) {
        RETURN_NULL();
    }

    php_sox_object *intern = Z_SOX_P(getThis());
    sox_effects_chain_t *chain = intern->chain;
    sox_effect_t *effect = sox_create_effect(sox_find_effect("treble"));

    char gain_str[20], freq_str[20], width_str[20];
    snprintf(gain_str, sizeof(gain_str), "%.2f", gain_db);
    snprintf(freq_str, sizeof(freq_str), "%.0f", freq);
    snprintf(width_str, sizeof(width_str), "%.0f", width);

    char *argv[] = { "treble", gain_str, freq_str, width_str };
    sox_effect_options(effect, 4, argv);
    chain_add_effect(chain, effect);
}

/********************************************************************************************************************
  TREMOLO (float $speed = 0, float $depth = 0)
********************************************************************************************************************/
PHP_METHOD(Sox, tremolo)
{
    double speed, depth;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_DOUBLE(speed)
        Z_PARAM_DOUBLE(depth)
    ZEND_PARSE_PARAMETERS_END();

    apply_tremolo_effect(getThis(), speed, depth);
}

/********************************************************************************************************************
  TRIM (float $start = 0, float $duration = 10)
********************************************************************************************************************/
PHP_METHOD(Sox, trim)
{
    long start, duration;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &start, &duration) == FAILURE) {
        RETURN_FALSE;
    }

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    char *start_str;
    char *duration_str;
    asprintf(&start_str, "%ld", start);
    asprintf(&duration_str, "%ld", duration);
    char *splice_args[] = {start_str, duration_str};
    apply_single_effect(obj, "splice", 2, splice_args TSRMLS_CC);
    free(start_str);
    free(duration_str);
}

/********************************************************************************************************************
  VAD (float $initial_trim = 0, float $trigger_level = 0.71)
********************************************************************************************************************/
PHP_METHOD(Sox, vad)
{
    double initial_trim, trigger_level;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_DOUBLE(initial_trim)
        Z_PARAM_DOUBLE(trigger_level)
    ZEND_PARSE_PARAMETERS_END();

    php_sox_object *obj = Z_SOX_P(getThis());

    if (!obj->input_file) {
        zend_throw_exception(zend_ce_exception, "No audio file has been loaded.", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *eff = sox_create_effect(sox_find_effect("vad"));

    char initial_trim_str[50], trigger_level_str[50];
    snprintf(initial_trim_str, sizeof(initial_trim_str), "%lf", initial_trim);
    snprintf(trigger_level_str, sizeof(trigger_level_str), "%lf", trigger_level);
    char *argv[] = {initial_trim_str, trigger_level_str};
    sox_effect_options(eff, 2, argv);
    chain_add_effect(obj, eff);
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
  STATIC UTILITY FUNCTIONS
********************************************************************************************************************/
void apply_chorus_effect(zval *obj, double gain_in, double gain_out, double delay, double decay, double speed, double depth)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("chorus"));
    char gain_in_str[20], gain_out_str[20], delay_str[20], decay_str[20], speed_str[20], depth_str[20];

    snprintf(gain_in_str, sizeof(gain_in_str), "%f", gain_in);
    snprintf(gain_out_str, sizeof(gain_out_str), "%f", gain_out);
    snprintf(delay_str, sizeof(delay_str), "%f", delay);
    snprintf(decay_str, sizeof(decay_str), "%f", decay);
    snprintf(speed_str, sizeof(speed_str), "%f", speed);
    snprintf(depth_str, sizeof(depth_str), "%f", depth);

    const char *options[] = {gain_in_str, gain_out_str, delay_str, decay_str, speed_str, depth_str};
    sox_effect_options(effect, 6, (char **)options);
    chain_add_effect(sox_object, effect);
}

void apply_echo_effect(zval *obj, double gain_in, double gain_out, double delay, double decay)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("echo"));
    char gain_in_str[20], gain_out_str[20], delay_str[20], decay_str[20];

    snprintf(gain_in_str, sizeof(gain_in_str), "%f", gain_in);
    snprintf(gain_out_str, sizeof(gain_out_str), "%f", gain_out);
    snprintf(delay_str, sizeof(delay_str), "%f", delay);
    snprintf(decay_str, sizeof(decay_str), "%f", decay);

    const char *options[] = {gain_in_str, gain_out_str, delay_str, decay_str};
    sox_effect_options(effect, 4, (char **)options);
    chain_add_effect(sox_object, effect);
}

void apply_equalizer_effect(zval *obj, double frequency, double width, double gain)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("equalizer"));
    char frequency_str[20], width_str[20], gain_str[20];

    snprintf(frequency_str, sizeof(frequency_str), "%f", frequency);
    snprintf(width_str, sizeof(width_str), "%f", width);
    snprintf(gain_str, sizeof(gain_str), "%f", gain);

    const char *options[] = {frequency_str, width_str, gain_str};
    sox_effect_options(effect, 3, (char **)options);
    chain_add_effect(sox_object, effect);
}

void apply_flanger_effect(zval *obj, double delay, double depth, double regen, double width, double speed, char *shape, char *phase, char *interpolation)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("flanger"));
    char delay_str[20], depth_str[20], regen_str[20], width_str[20], speed_str[20];

    snprintf(delay_str, sizeof(delay_str), "%f", delay);
    snprintf(depth_str, sizeof(depth_str), "%f", depth);
    snprintf(regen_str, sizeof(regen_str), "%f", regen);
    snprintf(width_str, sizeof(width_str), "%f", width);
    snprintf(speed_str, sizeof(speed_str), "%f", speed);

    const char *options[] = {delay_str, depth_str, regen_str, width_str, speed_str, shape, phase, interpolation};
    sox_effect_options(effect, 8, (char **)options);
    chain_add_effect(sox_object, effect);
}

void apply_phaser_effect(zval *obj, double gain_in, double gain_out, double delay, double decay, double speed)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("phaser"));
    char gain_in_str[20], gain_out_str[20], delay_str[20], decay_str[20], speed_str[20];

    snprintf(gain_in_str, sizeof(gain_in_str), "%f", gain_in);
    snprintf(gain_out_str, sizeof(gain_out_str), "%f", gain_out);
    snprintf(delay_str, sizeof(delay_str), "%f", delay);
    snprintf(decay_str, sizeof(decay_str), "%f", decay);
    snprintf(speed_str, sizeof(speed_str), "%f", speed);

    const char *options[] = {gain_in_str, gain_out_str, delay_str, decay_str, speed_str};
    sox_effect_options(effect, 5, (char **)options);
    chain_add_effect(sox_object, effect);
}

void apply_reverb_effect(zval *obj, double reverberance, double hf_damping, double room_scale, double stereo_depth, double pre_delay, double wet_gain)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("reverb"));
    char reverberance_str[20], hf_damping_str[20], room_scale_str[20], stereo_depth_str[20], pre_delay_str[20], wet_gain_str[20];

    snprintf(reverberance_str, sizeof(reverberance_str), "%f", reverberance);
    snprintf(hf_damping_str, sizeof(hf_damping_str), "%f", hf_damping);
    snprintf(room_scale_str, sizeof(room_scale_str), "%f", room_scale);
    snprintf(stereo_depth_str, sizeof(stereo_depth_str), "%f", stereo_depth);
    snprintf(pre_delay_str, sizeof(pre_delay_str), "%f", pre_delay);
    snprintf(wet_gain_str, sizeof(wet_gain_str), "%f", wet_gain);

    const char *options[] = {reverberance_str, hf_damping_str, room_scale_str, stereo_depth_str, pre_delay_str, wet_gain_str};
    sox_effect_options(effect, 6, (char **)options);
    chain_add_effect(sox_object, effect);
}

// Add a function to apply a single effect with given arguments
static void apply_single_effect(php_sox_object *obj, const char *effect_name, int argc, char **argv TSRMLS_DC) {
    sox_effects_chain_t *chain = sox_create_effects_chain(&obj->input_file->encoding, &obj->input_file->encoding);
    sox_effect_t *effect = sox_create_effect(sox_find_effect(effect_name));
    sox_effect_options(effect, argc, argv);
    sox_add_effect(chain, effect, &obj->input_file->signal, &obj->input_file->signal);
    sox_flow_effects(chain, NULL, NULL);
    sox_delete_effects_chain(chain);
}

void apply_tremolo_effect(zval *obj, double speed, double depth)
{
    php_sox_object *sox_object = Z_PHP_SOX_OBJECT_P(obj);

    sox_effect_t *effect = sox_create_effect(sox_find_effect("tremolo"));
    char speed_str[20], depth_str[20];

    snprintf(speed_str, sizeof(speed_str), "%f", speed);
    snprintf(depth_str, sizeof(depth_str), "%f", depth);

    const char *options[] = {speed_str, depth_str};
    sox_effect_options(effect, 2, (char **)options);
    chain_add_effect(sox_object, effect);
}

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