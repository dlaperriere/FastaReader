# print path of dir with perl.h header file

use Config; 
print "$Config{archlib}/CORE\n";
