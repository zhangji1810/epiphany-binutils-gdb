# ld: -T overlay.t -u __load_start_text1 -u __load_start_text2 -u __load_stop_text1 -u __load_stop_text2
#readelf: -s
#notarget: spu-*-*
# The SPU adds its own LOAD segments, out of order, at the start of the program header table.

#...
[ 	]+[0-9]+:[ 	]+0*4000[ 	]+0[ 	]+NOTYPE[ 	]+GLOBAL[ 	]+DEFAULT[ 	]+ABS __load_start_text1
#...
[ 	]+[0-9]+:[ 	]+0*4010[ 	]+0[ 	]+NOTYPE[ 	]+GLOBAL[ 	]+DEFAULT[ 	]+ABS __load_start_text2
#...
[ 	]+[0-9]+:[ 	]+0*4030[ 	]+0[ 	]+NOTYPE[ 	]+GLOBAL[ 	]+DEFAULT[ 	]+ABS __load_stop_text2
#...
[ 	]+[0-9]+:[ 	]+0*4010[ 	]+0[ 	]+NOTYPE[ 	]+GLOBAL[ 	]+DEFAULT[ 	]+ABS __load_stop_text1
#pass
