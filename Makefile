run:
	make -C build -j 16
	build/tracer
	magick out.ppm out.png
	feh out.png

%.spv: %.clcpp
	# clang -c -cl-std=clc++ -target spir -O0 -emit-llvm -o $^.bc $^
	clang -c -target spir64 -O0 -emit-llvm -o $^.bc $^
	llvm-spirv $^.ll -o $@
