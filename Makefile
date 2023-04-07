%.spv: %.clcpp
	# clang -c -cl-std=clc++ -target spir -O0 -emit-llvm -o $^.bc $^
	clang -c -target spir64 -O0 -emit-llvm -o $^.bc $^
	llvm-spirv $^.ll -o $@
