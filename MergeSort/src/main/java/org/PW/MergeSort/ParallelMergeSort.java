package org.PW.MergeSort;

import java.util.concurrent.RecursiveAction;

import static org.PW.MergeSort.Engine.merge;

public class ParallelMergeSort extends RecursiveAction {
    private final int[] array;
    private final int[] helper;
    private final int begin;
    private final int end;

    public ParallelMergeSort(final int[] array, final int begin, final int end) {
        this.array = array;
        helper = new int[array.length];
        this.begin = begin;
        this.end = end;
    }

    @Override
    protected void compute() {
        if (begin < end) {
            final int middle = (begin + end) / 2;
            final ParallelMergeSort left = new ParallelMergeSort(array, begin, middle);
            final ParallelMergeSort right = new ParallelMergeSort(array, middle + 1, end);
            invokeAll(left, right);
            merge(array, helper, begin, middle, end);
        }
    }
}
