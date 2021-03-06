package org.PW.MergeSort;

import org.junit.jupiter.api.Test;

import java.util.concurrent.ForkJoinPool;

import static org.PW.MergeSort.Engine.random;
import static org.junit.jupiter.api.Assertions.fail;


public class MergeSortTest {
    private static void check(final int[] array) {
        int last = Integer.MIN_VALUE;
        for (int i = 0; i < array.length; i++) {
            if (array[i] < last) {
                fail();
            }

            last = array[i];
        }
    }
    @Test
    public void SequenceTest(){
        final int [] array = random(1000);{
          MergeSort.mergesort(array);
        }
        check(array);
    }

    @Test
    public void ParallelTest(){
        final int[] array = random(1000);
        final ForkJoinPool forkJoinPool = new ForkJoinPool(7);
        forkJoinPool.invoke(new ParallelMergeSort(array,0,array.length-1));
    check(array);
    }
}
