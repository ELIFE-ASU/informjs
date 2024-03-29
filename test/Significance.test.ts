import { Significance } from '../src';
import * as seed from 'seedrandom';

describe('check exports', () => {
    test('.has mutualInfo', () => expect(Significance.mutualInfo).toBeDefined());
    test('.has activeInfo', () => expect(Significance.activeInfo).toBeDefined());
    test('.has transferEntropy', () => expect(Significance.transferEntropy).toBeDefined());
});

describe('mutual information', () => {
    const rng = seed('2019');
    const { mutualInfo } = Significance;

    test('.throws for too-few permutations', () => {
        expect(() => mutualInfo([0, 0, 1, 1], [0, 1, 0, 1], -1, rng)).toThrow(/too few/);
        expect(() => mutualInfo([0, 0, 1, 1], [0, 1, 0, 1], 0, rng)).toThrow(/too few/);
        expect(() => mutualInfo([0, 0, 1, 1], [0, 1, 0, 1], 1, rng)).toThrow(/too few/);
        expect(() => mutualInfo([0, 0, 1, 1], [0, 1, 0, 1], 9, rng)).toThrow(/too few/);
    });

    test.each`
        xs                          | ys                          | nperm   | value            | p           | se
        ${[0, 0, 0, 0, 0, 0, 0, 0]} | ${[0, 0, 0, 0, 0, 0, 0, 0]} | ${1000} | ${[0, 6]}        | ${[1, 6]}   | ${[0, 6]}
        ${[0, 0, 0, 0, 0, 0, 0, 1]} | ${[0, 0, 0, 0, 0, 0, 0, 1]} | ${1000} | ${[0.543564, 6]} | ${[0.1, 1]} | ${[0.01, 2]}
    `('.can', ({ xs, ys, nperm, value, p, se }) => {
        let mi = mutualInfo(xs, ys, nperm, rng);
        expect(mi.value).toBeCloseTo(value[0], value[1]);
        expect(mi.sig.p).toBeCloseTo(p[0], p[1]);
        expect(mi.sig.se).toBeCloseTo(se[0], se[1]);

        mi = mutualInfo(ys, xs, nperm, rng);
        expect(mi.value).toBeCloseTo(value[0], value[1]);
        expect(mi.sig.p).toBeCloseTo(p[0], p[1]);
        expect(mi.sig.se).toBeCloseTo(se[0], se[1]);
    });
});

describe('active information', () => {
    const rng = seed('2019');
    const { activeInfo } = Significance;

    test('.throws for too-few permutations', () => {
        expect(() => activeInfo([0, 0, 1, 1], 2, -1, rng)).toThrow(/too few/);
        expect(() => activeInfo([0, 0, 1, 1], 2, 0, rng)).toThrow(/too few/);
        expect(() => activeInfo([0, 0, 1, 1], 2, 1, rng)).toThrow(/too few/);
        expect(() => activeInfo([0, 0, 1, 1], 2, 9, rng)).toThrow(/too few/);
    });

    test.each`
        xs                          | k    | nperm   | value            | p                | se
        ${[0, 0, 0, 0, 0, 0, 0, 0]} | ${2} | ${1000} | ${[0, 6]}        | ${[1, 6]}        | ${[0, 6]}
        ${[0, 0, 0, 0, 0, 0, 0, 1]} | ${2} | ${1000} | ${[0, 6]}        | ${[1, 6]}        | ${[0, 6]}
        ${[0, 0, 0, 0, 0, 0, 1, 1]} | ${2} | ${1000} | ${[0.316689, 6]} | ${[0.447552, 6]} | ${[0.015716, 6]}
        ${[0, 0, 0, 0, 0, 1, 1, 1]} | ${2} | ${1000} | ${[0.459148, 6]} | ${[0.402597, 1]} | ${[0.015501, 6]}
        ${[1, 0, 1, 0, 1, 0, 1, 0]} | ${2} | ${1000} | ${[1, 6]}        | ${[0.056943, 6]} | ${[0.007324, 2]}
    `('.can', ({ xs, k, nperm, value, p, se }) => {
        let ai = activeInfo(xs, k, nperm, rng);
        expect(ai.value).toBeCloseTo(value[0], value[1]);
        expect(ai.sig.p).toBeCloseTo(p[0], p[1]);
        expect(ai.sig.se).toBeCloseTo(se[0], se[1]);
    });
});

describe('transfer entropy', () => {
    const rng = seed('2019');
    const { transferEntropy } = Significance;

    test('.throws for too-few permutations', () => {
        expect(() => transferEntropy([0, 0, 1, 1], [0, 1, 0, 1], 2, -1, rng)).toThrow(/too few/);
        expect(() => transferEntropy([0, 0, 1, 1], [0, 1, 0, 1], 2, 0, rng)).toThrow(/too few/);
        expect(() => transferEntropy([0, 0, 1, 1], [0, 1, 0, 1], 2, 1, rng)).toThrow(/too few/);
        expect(() => transferEntropy([0, 0, 1, 1], [0, 1, 0, 1], 2, 9, rng)).toThrow(/too few/);
    });

    test('.can', () => {
        let te = transferEntropy([0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0], 2, 1000, rng);
        expect(te.value).toBeCloseTo(0, 6);
        expect(te.sig.p).toBeCloseTo(1, 6);
        expect(te.sig.se).toBeCloseTo(0, 6);

        te = transferEntropy([0, 0, 1, 0, 0, 0, 0, 0], [0, 0, 0, 1, 0, 0, 0, 0], 2, 1000, rng);
        expect(te.value).toBeCloseTo(0.540852, 6);
        expect(te.sig.p).toBeCloseTo(0.1, 1);
        expect(te.sig.se).toBeCloseTo(0.01, 2);

        te = transferEntropy([0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0], 2, 1000);
        expect(te.value).toBeCloseTo(0, 6);
        expect(te.sig.p).toBeCloseTo(1, 6);
        expect(te.sig.se).toBeCloseTo(0, 6);

        te = transferEntropy([0, 0, 1, 0, 0, 0, 0, 0], [0, 0, 0, 1, 0, 0, 0, 0], 2, 1000);
        expect(te.value).toBeCloseTo(0.540852, 6);
        expect(te.sig.p).toBeCloseTo(0.1, 1);
        expect(te.sig.se).toBeCloseTo(0.01, 2);
    });
});
