#ifndef PHP_SOX_H
#define PHP_SOX_H 1

#include "php.h"
#include "sox.h"

#define PHP_SOX_VERSION "1.0"
#define PHP_SOX_EXTNAME "sox"

extern zend_module_entry sox_module_entry;
#define phpext_sox_ptr &sox_module_entry

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

#endif
