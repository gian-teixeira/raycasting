cc='gcc'
flags="-lraylib -lm" #-lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lraylib -lm"
src_folder='src'
build_folder='build'
bin_folder='bin'
pname='none'

mkdir -p $build_folder
mkdir -p $bin_folder

for cfile in $(find "${src_folder}" -name '*.c'); do
    filename=$(basename $cfile .c)
    obj="$build_folder/$filename.o"
    $cc -c $cfile $flags -o $obj
done

$cc $(find $build_folder -name '*.o') $flags -o "${bin_folder}/${pname}"
