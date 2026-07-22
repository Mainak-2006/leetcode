import java.util.*;

class Solution {
    public List<Integer> maxActiveSectionsAfterTrade(String s, int[][] queries) {
        final int n = s.length();
        final char[] c = s.toCharArray();

        // --- count ones without streams ---
        int ones = 0;
        for (int i = 0; i < n; i++) if (c[i] == '1') ones++;

        // --- build zero groups as flat primitive arrays (no Group objects, no Pair) ---
        int[] gStart = new int[n];
        int[] gLen = new int[n];
        int[] zeroGroupIndex = new int[n];
        int groupCount = 0;

        for (int i = 0; i < n; i++) {
            if (c[i] == '0') {
                if (i > 0 && c[i - 1] == '0') {
                    gLen[groupCount - 1]++;
                } else {
                    gStart[groupCount] = i;
                    gLen[groupCount] = 1;
                    groupCount++;
                }
            }
            zeroGroupIndex[i] = groupCount - 1;
        }

        final int q = queries.length;
        List<Integer> ans = new ArrayList<>(q); // preallocate, avoid resizing

        if (groupCount == 0) {
            Integer boxedOnes = ones; // box once, reuse
            for (int i = 0; i < q; i++) ans.add(boxedOnes);
            return ans;
        }

        // --- sparse table over merge-lengths of adjacent zero groups ---
        final int m = groupCount - 1;
        int[][] st = null;
        if (m > 0) {
            int[] base = new int[m];
            for (int i = 0; i < m; i++) base[i] = gLen[i] + gLen[i + 1];

            int LOG = 32 - Integer.numberOfLeadingZeros(m); // number of levels
            st = new int[LOG][];
            st[0] = base;
            for (int k = 1; k < LOG; k++) {
                int half = 1 << (k - 1);
                int len = m - (1 << k) + 1;
                int[] prev = st[k - 1];
                int[] row = new int[len];
                for (int j = 0; j < len; j++)
                    row[j] = Math.max(prev[j], prev[j + half]);
                st[k] = row;
            }
        }

        for (int[] query : queries) {
            final int l = query[0];
            final int r = query[1];
            final int lg = zeroGroupIndex[l];
            final int rg = zeroGroupIndex[r];

            final int left = (lg == -1) ? -1 : (gLen[lg] - (l - gStart[lg]));
            final int right = (rg == -1) ? -1 : (r - gStart[rg] + 1);

            // computed once, reused (original code evaluated this ternary twice)
            final int rEndGroup = (c[r] == '1') ? rg : rg - 1;
            final int startAdj = lg + 1;
            final int endAdj = rEndGroup - 1;

            int active = ones;

            if (c[l] == '0' && c[r] == '0' && lg + 1 == rg) {
                final int cand = ones + left + right;
                if (cand > active) active = cand;
            } else if (startAdj <= endAdj) {
                final int k = 31 - Integer.numberOfLeadingZeros(endAdj - startAdj + 1);
                final int[] row = st[k];
                final int best = Math.max(row[startAdj], row[endAdj - (1 << k) + 1]);
                final int cand = ones + best;
                if (cand > active) active = cand;
            }

            if (c[l] == '0' && lg + 1 <= rEndGroup) {
                final int cand = ones + left + gLen[lg + 1];
                if (cand > active) active = cand;
            }
            if (c[r] == '0' && lg < rg - 1) {
                final int cand = ones + right + gLen[rg - 1];
                if (cand > active) active = cand;
            }

            ans.add(active);
        }

        return ans;
    }
}