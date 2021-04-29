package org.PW.MergeSort;

import java.util.Random;

public interface Engine {
    static int[] random(final int n) {
        final int[] a = new int[n];

        for (int i = 0; i < n; i++) {
            a[i] = new Random().nextInt(n);
        }

        return a;
    }

    static void merge(final int[] array, final int[] helper, final int begin, final int middle, final int end) {
        for (int i = begin; i <= end; i++) {
            helper[i] = array[i];
        }

        int helperLeft = begin;
        int helperRight = middle + 1;
        int current = begin;

        while (helperLeft <= middle && helperRight <= end) {
            if (helper[helperLeft] <= helper[helperRight]) {
                array[current] = helper[helperLeft++];
            } else {
                array[current] = helper[helperRight++];
            }
            current++;
        }

        while (helperLeft <= middle) {
            array[current++] = helper[helperLeft++];
        }
    }
}
