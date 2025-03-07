FROM gcc:14.2.0

WORKDIR /app
COPY Makefile /app/
COPY src /app/src

RUN make

ENTRYPOINT ["./main"]