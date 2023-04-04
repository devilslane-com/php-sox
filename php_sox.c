#include "php_sox.h"

// Define a class entry for the Sox class
zend_class_entry *sox_ce;

// Declare the Sox class methods
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
PHP_METHOD(Sox, EQ);
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

// Define the class method list
static const zend_function_entry sox_methods[] = {
    PHP_ME(Sox, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Sox, analyze, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, bass, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, chorus, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, compressor, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, concatenate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, convert, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, delay, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, dither, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, echo, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, EQ, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, extract_left, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, extract_right, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, fade, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, filter, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, formats, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, gain, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, load, NULL, ZEND_ACC_PUBLIC)
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
    PHP_ME(Sox, sample_rate, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, sample_size, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, save, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, segment, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, speed, NULL, ZEND_ACC_PUBLIC)
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
    PHP_ME(Sox, visualize, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Sox, volume, NULL, ZEND_ACC_PUBLIC)
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

// Sox class constructor
PHP_METHOD(Sox, __construct)
{
    // Initialize the SoX library
    if (sox_init() != SOX_SUCCESS) {
        zend_throw_exception(zend_ce_exception, "Failed to initialize SoX library", 0 TSRMLS_CC);
        return;
    }
}

// Sox class load method
PHP_METHOD(Sox, load)
{
    char *input_file_path;
    size_t input_file_path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &input_file_path, &input_file_path_len) == FAILURE) {
        RETURN_FALSE;
    }

    sox_format_t *input_file = sox_open_read(input_file_path, NULL, NULL, NULL);

    if (!input_file) {
        sox_quit();
        zend_throw_exception(zend_ce_exception, "Failed to open input file", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    // Store the input_file as a property in the Sox object
    zend_update_property_stringl(sox_ce, getThis(), "input_file", strlen("input_file"), (char *)&input_file, sizeof(sox_format_t) TSRMLS_CC);
}

// Sox class save method
PHP_METHOD(Sox, save)
{
    char *output_file_path;
    size_t output_file_path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &output_file_path, &output_file_path_len) == FAILURE) {
        RETURN_FALSE;
    }

    sox_format_t *input_file;
    zval *input_file_zval = zend_read_property(sox_ce, getThis(), "input_file", strlen("input_file"), 0 TSRMLS_CC);
    if (Z_TYPE_P(input_file_zval) != IS_STRING) {
        zend_throw_exception(zend_ce_exception, "No input file loaded", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    input_file = (sox_format_t *) Z_STRVAL_P(input_file_zval);

    sox_format_t *output_file = sox_open_write(output_file_path, &input_file->signal, NULL, NULL, NULL, NULL);

    if (!output_file) {
        sox_quit();
        zend_throw_exception(zend_ce_exception, "Failed to open output file", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effects_chain_t *chain = sox_create_effects_chain(&input_file->encoding, &output_file->encoding);

    if (!chain) {
        sox_quit();
        zend_throw_exception(zend_ce_exception, "Failed to create effects chain", 0 TSRMLS_CC);
        RETURN_FALSE;
    }

    sox_effect_t *effect = sox_create_effect(sox_find_effect("input"));
    char *args[] = { (char *)input_file };
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &input_file->signal, &input_file->signal);

    // Add other effects here

    effect = sox_create_effect(sox_find_effect("output"));
    args[0] = (char *)output_file;
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &input_file->signal, &output_file->signal);

    sox_flow_effects(chain, NULL, NULL);

    // Cleanup
    sox_delete_effects_chain(chain);
    sox_close(output_file);
    sox_close(input_file);
    sox_quit();

    RETURN_TRUE;
}