set DST_DIR=D:\work\TripleS\TripleS\Shared
set SRC_DIR=D:\work\TripleS\TripleS\Proto
protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/tutorial.proto