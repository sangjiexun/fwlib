from strangesast/fwlib as base

from base as builder

copy build-deps.sh /tmp/
run /tmp/build-deps.sh

workdir /usr/src/app

copy example/ .

run mkdir build && \
  cd build && \
  cmake .. && \
  make && \
  make test

from base

copy --from=builder /usr/src/app/build/bin/fanuc_example /usr/local/bin/

cmd fanuc_example
