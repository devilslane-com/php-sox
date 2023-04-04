# Sound eXchange (Sox) Audio Extension for PHP

This extension provides bindings for the SoX (Sound eXchange) library, enabling audio processing capabilities in PHP.

## Requirements

- PHP development environment (header files and libraries)
- SoX library and development files (header files and libraries)

## What is Sox?

Sox is the "Swiss Army knife of sound processing programs".

SoX is a cross-platform (Windows, Linux, MacOS X, etc.) command line utility that can convert various formats of computer audio files in to other formats. It can also apply various effects to these sound files, and, as an added bonus, SoX can play and record audio files on most platforms.

## API Functions

### Loading and saving

```php
// Create a new Sox instance
$sox = new Sox();

// Load an audio file
$sox->load("path/to/your/input_audio_file.wav");

// Save the processed audio to a file
$sox->save("path/to/your/output_audio_file.wav");
```

### Utilities

```php
// Create a new Sox instance
$sox = new Sox();

$sox->analyze("path/to/your/audiofile.wav") : array
$sox->formats() : array
$sox->version() : string
$sox->visualize("path/to/your/audiofile.wav", "path/to/your/spectrogram_image.png") : bool // generate a spectrogram
```

### Processing

```php
// Create a new Sox instance
$sox = new Sox();

// Load an audio file
$sox->load("path/to/your/input_audio_file.wav");

$sox->bass() : bool
$sox->chorus() : bool
$sox->compressor() : bool
$sox->concatenate((array )['path/to/audio1.wav', 'path/to/audio2.wav', 'path/to/audio3.wav']) : bool
$sox->convert("mp3") : bool
$sox->delay() : bool
$sox->dither() : bool
$sox->echo() : bool
$sox->eq() : bool
$sox->extract_left() : bool
$sox->extract_right() : bool
$sox->fade() : bool
$sox->filter() : bool
$sox->gain() : bool
$sox->loudness() : bool
$sox->metadata() : bool
$sox->mix([], ''): bool
$sox->noise() : bool
$sox->normalize() : bool
$sox->pad() : bool
$sox->phaser() : bool
$sox->pitch() : bool
$sox->repeat() : bool
$sox->reverb() : bool
$sox->reverse() : bool
$sox->sample_rate() : bool
$sox->sample_size() : bool
$sox->segment() : bool
$sox->speed((float) 1.7) : bool
$sox->splice() : bool
$sox->stretch() : bool
$sox->swap() : bool // channels
$sox->tempo() : bool
$sox->to_mono() : bool
$sox->to_stereo() : bool
$sox->treble() : bool
$sox->tremolo() : bool
$sox->trim() : bool
$sox->vad() : bool
$sox->volume() : bool
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

