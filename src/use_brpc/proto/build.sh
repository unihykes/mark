
#!/bin/bash

${MK_DEPS_PKGS}/protobuf/bin/protoc  --cpp_out=./ --proto_path=./  use_brpc.proto