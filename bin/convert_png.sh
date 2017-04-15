#!/bin/bash
#Pass absolute or relative paths to tga files as arguments.
#Or use wildcards *.tga to specify all tga files in working directory.
for tga; do                                 
    png="${tga%.tga}.png"                    
    echo converting "$tga"              
    convert "$tga" "$png"
done                                    
