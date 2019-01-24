# berkeley cs61c 2015

Great Ideas in Computer Architecture (Machine Structures)

[course website](http://inst.eecs.berkeley.edu/~cs61c/sp15) contain all course resource

[video playlist](https://www.youtube.com/playlist?list=PLhMnuBfGeCDM8pXLpqib90mDFJI-e1lpk) has course video

# mips compiler

use docker container to run mips gcc compiler, 32-bit ISA
`docker run -it --name mips -v "$(pwd)":/berkeley/cs61c dockcross/linux-mips bash` start container
`$CC --args` use mips-gcc compile code
