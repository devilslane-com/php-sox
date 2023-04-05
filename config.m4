dnl config.m4 for extension sox

PHP_ARG_ENABLE(sox, whether to enable sox support,
[  --enable-sox           Enable sox support])

if test "$PHP_SOX" = "yes"; then
  AC_DEFINE(HAVE_SOX, 1, [Whether you have sox])

  PHP_REQUIRE_CXX()

  PHP_ADD_LIBRARY(sox, 1, SOX_SHARED_LIBADD)
  PHP_ADD_INCLUDE([/usr/include])
  PHP_SUBST(SOX_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sox, php_sox.c, $ext_shared)
fi
