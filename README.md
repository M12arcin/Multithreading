# Multithreading
Compare application written in java for parallel merge sort algorithm and merge sort algorithm. Both application compare with distrubed programming in C using MPI.
For test used Microbenchmarking.

```
	@Benchmark
	@Fork(value = 1, warmups = 1)
	@Warmup(iterations = 1)
	@Measurement(iterations = 3)
	@OutputTimeUnit(TimeUnit.MILLISECONDS)
	@BenchmarkMode(Mode.AverageTime)
	public void benchParallel() {
		final int[] array = Utils.random(SIZE);
		final ForkJoinPool forkJoinPool = new ForkJoinPool(Runtime.getRuntime().availableProcessors() - 1);
		forkJoinPool.invoke(new ParallelMergeSort(array, 0, array.length - 1));
		Arrays.parallelSort(array);
	}

```

```
   <dependency>
            <groupId>org.openjdk.jmh</groupId>
            <artifactId>jmh-core</artifactId>
            <version>1.19</version>
        </dependency>
        <dependency>
            <groupId>org.openjdk.jmh</groupId>
            <artifactId>jmh-generator-annprocess</artifactId>
            <version>1.19</version>
        </dependency>

```


