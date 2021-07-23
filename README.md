# funtartica
2D Game Engine with LUA scripts.

# Compile

The fastest compile:  
```bash
./configure  
make
```  
The advanced ./configure parameters:  
```bash
./configure <parameters>
```
Parameters:  
> -h,-help,--help  - This help message.  
> -c,--compiler [gcc|clang]  - Select compiler.  
> -d,--debug  - Enable debug mode.  
> --no-debug - Disable debug mode.  
> -l,--lua [luajit|lua51|lua53]  - Select LUA version.  
> -m,--mem  - Debug memory leak (sanitizer).  
> --no-mem  - Disable sanitizer memory leak debug.  

# Run  
```bash
./ge
```
