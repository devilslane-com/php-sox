# Sound eXchange (Sox) Audio Extension for PHP

This extension provides bindings for the SoX (Sound eXchange) library, enabling audio processing capabilities in PHP.

## Requirements

- PHP development environment (header files and libraries)
- SoX library and development files (header files and libraries)

## What is Sox?

Sox is the "Swiss Army knife of sound processing programs".

SoX is a cross-platform (Windows, Linux, MacOS X, etc.) command line utility that can convert various formats of computer audio files in to other formats. It can also apply various effects to these sound files, and, as an added bonus, SoX can play and record audio files on most platforms.

## Examples

### Increase audio volume by 50% and export as 128-bit MP3

```php
(new Sox)->load("input_audio_file.wav")
   ->volume(1.5)
   ->convert(128, 'mp3')
   ->save('output.mp3');
```

### Change to 16-bit 44Hz, increase gain by 6db, at 2x speed
```php
(new Sox)->load("input_audio_file.wav")
   ->sample_rate(44000)
   ->sample_size(16)
   ->gain(6)
   ->speed(2.0)
   ->save('output.wav');
```

## SoX Features

### Audio Formats

```
8svx aif aifc aiff aiffc al amb amr-nb amr-wb anb au avr awb caf cdda cdr cvs cvsd cvu dat dvms f32 f4 f64 f8 fap flac fssd gsm gsrt hcom htk ima ircam la lpc lpc10 lu mat mat4 mat5 maud mp2 mp3 nist ogg paf prc pvf raw s1 s16 s2 s24 s3 s32 s4 s8 sb sd2 sds sf sl sln smp snd sndfile sndr sndt sou sox sph sw txw u1 u16 u2 u24 u3 u32 u4 u8 ub ul uw vms voc vorbis vox w64 wav wavpcm wv wve xa xi
```

### Audio Effects

```
allpass band bandpass bandreject bass bend biquad chorus channels compand contrast dcshift deemph delay dither divide+ downsample earwax echo echos equalizer fade fir firfit+ flanger gain highpass hilbert input# ladspa loudness lowpass mcompand noiseprof noisered norm oops output# overdrive pad phaser pitch rate remix repeat reverb reverse riaa silence sinc spectrogram speed splice stat stats stretch swap synth tempo treble tremolo trim upsample vad vol
```

## Frequency Guide

```
+-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
| Instrument/Sound      |   50Hz |  100Hz |  200Hz |  500Hz | 1,000Hz| 2,000Hz| 5,000Hz|10,000Hz|20,000Hz|25,000Hz|
+-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
| Kick Drum             |    X   |    X   |    X   |        |        |        |        |        |        |        |
| Bass Guitar           |    X   |    X   |    X   |    X   |    X   |        |        |        |        |        |
| Electric Guitar       |        |        |    X   |    X   |    X   |    X   |    X   |        |        |        |
| Piano                 |    X   |    X   |    X   |    X   |    X   |    X   |    X   |    X   |        |        |
| Human Voice (Male)    |        |    X   |    X   |    X   |    X   |    X   |    X   |        |        |        |
| Human Voice (Female)  |        |        |    X   |    X   |    X   |    X   |    X   |    X   |        |        |
| Cymbals               |        |        |        |    X   |    X   |    X   |    X   |    X   |    X   |    X   |
| Violin                |        |        |    X   |    X   |    X   |    X   |    X   |    X   |        |        |
| Flute                 |        |        |        |    X   |    X   |    X   |    X   |    X   |        |        |
| Trumpet               |        |        |    X   |    X   |    X   |    X   |    X   |    X   |        |        |
| Sibilance (Ess sound) |        |        |        |        |        |        |    X   |    X   |    X   |    X   |
+-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+

```

## API Functions

### Loading and saving

```php
   // Create a new Sox instance
   $sox = new Sox();

   // Load an audio file
   $sox->load(string $file_path = "path/to/your/input_audio_file.wav");

   // Or load a list to combine together
   $sox->concatenate(array $chunks = ['path/to/audio1.wav', 'path/to/audio2.wav']);

   // Save the processed audio to a file
   $sox->save(string $save_path = "path/to/your/output_audio_file.wav");
```

### Utilities

```php
   // Create a new Sox instance
   $sox = new Sox();

   $sox->formats(); // array of supported formats
   $sox->version(); // string of libsox version

   // Load an audio file
   $sox->load(string $file_path = "path/to/your/input_audio_file.wav");

   $sox->analyze(); // array of data from the stat() function in libsox
   $sox->visualize(string $export_image_path = "path/to/your/spectrogram_image.png", int $width = 1024, int $height = 768, array $rgb_values = [100, 20, 56]); // generate a spectrogram with RGB colour values
```

### Chainable Processing

```php
   // Create a new Sox instance
   $sox = new Sox();

   // Load an audio file
   $sox->load(string $file_path = "path/to/your/input_audio_file.wav");

   $sox->bass(float $decibels = 1.0, float $frequency_hz = 400, float $width_hz = 100);
   $sox->chorus(float $gain_in = 1.0, float $gain_out = 0, float $delay_ms = 0, float $decay_ms = 0, float $speed_ms = 0, float $depth_ms = 0);
   $sox->compressor();
   $sox->concatenate(array $chunks = ['path/to/audio1.wav', 'path/to/audio2.wav']);
   $sox->convert(int $bitrate = 256, string $format = "mp3");
   $sox->delay();
   $sox->dither();
   $sox->echo(float $gain_in = 0, float $gain_out = 0, float $delay_ms = 0, float $decay_ms = 0);
   $sox->eq(float $frequency_hz = 1500, float $width_hz = 100, float $decibels = -3.5);
   $sox->extract_left();
   $sox->extract_right();
   $sox->fade(string $type = "in|out", int $length = 10);
   $sox->filter(string $type = "allpass|bandpass|bankreject|lowpass|highpass", float $frequency_hz = 1000, float $width_hz = 100); 
   $sox->flanger(float $delay_ms = 0, float $depth_ms = 0, float $regeneration_percent = 0, float $width_percent = 0, float $speed_hz = 0, string $shape = "sine|triangle", string $phase_percent, string $interpolation ="linear|quadratic");
   $sox->gain(float $decibels = 1.0);
   $sox->loudness(float $gain = 1.0, float $reference = 0.5);
   $sox->metadata(string $comment = "");
   $sox->mix(array $files = ['audio1.wav', 'audio2.wav']);
   $sox->noise(int $sample_from_ms = 0, int $sample_duration_ms = 10000, float $sensitivity = 0.21);
   $sox->normalize(int $decibels = 0);
   $sox->pad(float $start = 0, float $end = 400);
   $sox->phaser(float $gain_in = 0, float $gain_out = 0, float $delay_ms = 0, float $decay_ms = 0, float $speed_ms = 0);
   $sox->pitch(float $frequency_hz = -31);
   $sox->repeat(int $count = 5);
   $sox->reverb(float $reverberance_percent = 100, float $hf_damping_percent = 100, float $room_scale_percent = 100, float $stereo_depth_percent = 100, float $pre_delay_ms = 0, float $wet_gain_decibels = 0);
   $sox->reverse();
   $sox->sample_rate(int $hertz = 48000);
   $sox->sample_size(int $bits = 16);
   $sox->segment(float $start = 0, float $duration = 10);
   $sox->speed(float $factor = 1.2);
   $sox->splice(float $position = 20);
   $sox->stretch(float $factor = 1.0);
   $sox->swap(); // left/right channels
   $sox->tempo(float $factor = 1.0);
   $sox->to_mono();
   $sox->to_stereo();
   $sox->treble(float $decibels = 2.0, float $frequency_hz = 3500, float $width_hz = 100);
   $sox->tremolo(float $speed_ms = 0, float $depth_ms = 0);
   $sox->trim(float $start = 50, float $duration = 5);
   $sox->vad(float $initial_trim = 0, float $trigger_level = 0.71);
   $sox->volume(float $factor = 1.5);
```


## Building and Compiling on Unix and macOS

1. Install the SoX library:
   On Unix-based systems, you can install the SoX library and its development files through the package manager:
   - For Ubuntu/Debian:
     ```
     sudo apt-get install libsox-dev
     ```
   - For CentOS/RHEL/Fedora:
     ```
     sudo yum install sox-devel
     ```
   - For macOS, you can install the SoX library using Homebrew:
     ```
     brew install sox
     ```

2. Set up the PHP development environment:
   Make sure you have PHP and its development files installed on your system. You can usually install them using the package manager or by compiling PHP from source.

3. Build and compile the extension:
   - Copy the `php_sox` extension folder (containing `config.m4`, `php_sox.c`, and `php_sox.h`) to a suitable location.
   - Open a terminal and navigate to the `php_sox` extension directory.
   - Run the following commands:
     ```
     phpize
     ./configure --enable-sox
     make
     sudo make install
     ```

4. Enable the extension:
   - Locate the `php.ini` file used by your PHP installation. You can find the path by running `php --ini`.
   - Open the `php.ini` file and add the following line:
     ```
     extension=sox.so
     ```
   - Restart your web server or PHP-FPM to enable the extension.

## Building and Compiling on Windows

1. Install the SoX library:
   Download and install the SoX library (http://sox.sourceforge.net/) on your system. Make sure that the library (`sox.lib`) and header file (`sox.h`) are located in the appropriate directories.

2. Set up the PHP development environment:
   Download the PHP source code and extract it to a directory. Download and install the PHP SDK (https://github.com/microsoft/php-sdk-binary-tools) to build PHP extensions.

3. Build and compile the extension:
   - Copy the `php_sox` extension folder (containing `config.w32`, `php_sox.c`, and `php_sox.h`) into the `ext` folder of the PHP source code directory.
   - Open a command prompt and navigate to the PHP source code directory.
   - Run the following commands:
     ```
     buildconf
     configure --disable-all --enable-cli --enable-sox
     nmake
     ```

4. Enable the extension:
   - Find the compiled `php_sox.dll` file in the `Release_TS` or `Debug_TS` folder, depending on your build configuration.
   - Copy `php_sox.dll` to the `ext` folder in your PHP installation directory.
   - Open the `php.ini` file and add the following line:
     ```
     extension=php_sox.dll
     ```
   - Restart your web server or PHP-FPM to enable the extension.

