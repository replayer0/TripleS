set CPP_DST_DIR=.
set CSHARP_DST_DIR=.
set SRC_DIR=.
set PROTO_SRC_DIR=.

protoc -I=%SRC_DIR% --cpp_out=%CPP_DST_DIR% %PROTO_SRC_DIR%/packet.proto

protogen %PROTO_SRC_DIR%/packet.proto --proto_path=%CSHARP_DST_DIR%