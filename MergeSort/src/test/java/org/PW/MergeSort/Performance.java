package org.PW.MergeSort;

import org.openjdk.jmh.annotations.*;

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.TimeUnit;

import static org.PW.MergeSort.Engine.merge;
import static org.PW.MergeSort.Engine.random;

public class Performance {

    private static final int SIZE = 100000;

    public static void main(String[] args) throws Exception {
        org.openjdk.jmh.Main.main(args);
    }

    @Benchmark
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 1)
    @Measurement(iterations = 10)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    @BenchmarkMode(Mode.AverageTime)
    public void PerformanceSequence() {
        final int[] array = random(SIZE);
        MergeSort.mergesort(array);
    }

    @Benchmark
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 1)
    @Measurement(iterations = 10)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    @BenchmarkMode(Mode.AverageTime)
    public void PerformanceParallel() {
        final int[] array = random(SIZE);
        final ForkJoinPool forkJoinPool = new ForkJoinPool(Runtime.getRuntime().availableProcessors() - 1);
        forkJoinPool.invoke(new ParallelMergeSort(array, 0, array.length - 1));
        Arrays.parallelSort(array);
    }
}
