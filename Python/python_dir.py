#!env python

# print python include dir
# based on python-conifg

from distutils import sysconfig

pyver = sysconfig.get_config_var('VERSION')
getvar = sysconfig.get_config_var

flags = ['-I' + sysconfig.get_python_inc(),
         '-I' + sysconfig.get_python_inc(plat_specific=True)]
print ' '.join(flags)
