package org.PW.MergeSort;

import static org.PW.MergeSort.Engine.merge;

public class MergeSort {
    public static void mergesort(final int[] array) {
        final int[] helper = new int[array.length];
        mergesort(array, helper, 0, array.length - 1);
    }

    public static void mergesort(final int[] array, final int[] helper, final int low, final int high) {
        if (low < high) {
            final int middle = (low + high) / 2;
            mergesort(array, helper, low, middle);
            mergesort(array, helper, middle + 1, high);
            merge(array, helper, low, middle, high);
        }
    }
}
