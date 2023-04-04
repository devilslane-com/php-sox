PHP_ARG_ENABLE(php_sox, whether to enable SoX support,
[ --enable-php_sox       Enable SoX support])

if test "$PHP_PHP_SOX" = "yes"; then
  AC_CHECK_LIB(sox, sox_open_read, [
    AC_CHECK_HEADER(sox.h, [
      PHP_ADD_LIBRARY(sox, 1)
      AC_DEFINE(HAVE_SOX, 1, [Whether you have SoX Library])
    ])
  ])

  PHP_NEW_EXTENSION(php_sox, php_sox.c, $ext_shared)
fi