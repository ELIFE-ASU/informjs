import { mutualInfo } from '../src';

describe('mutual information', () => {
    test('.throws for different lengths', () => {
        expect(() => mutualInfo([], [0])).toThrow(/different lengths/);
        expect(() => mutualInfo([0], [])).toThrow(/different lengths/);
    });

    test('.throws for empty', () => {
        expect(() => mutualInfo([], [])).toThrow(/NULL/);
    });

    test('.invalid element', () => {
        expect(() => mutualInfo([-1, 0, 0], [1, 1, 0])).toThrow(/negative/);
        expect(() => mutualInfo([1, 0, 0], [-1, 1, 0])).toThrow(/negative/);
        expect(() => mutualInfo([1, 0, 0], [-1, 1, 0])).toThrow(/negative/);
    });

    test('.can', () => {
        expect(mutualInfo([0, 0, 0, 0, 1, 1, 1, 1], [1, 1, 1, 1, 0, 0, 0, 0])).toBeCloseTo(1.0, 6);

        expect(mutualInfo([0, 0, 1, 1, 1, 1, 0, 0, 0], [1, 1, 0, 0, 0, 0, 1, 1, 1])).toBeCloseTo(0.991076, 6);

        expect(mutualInfo([1, 1, 0, 1, 0, 1, 1, 1, 0], [1, 1, 0, 0, 0, 1, 0, 1, 1])).toBeCloseTo(0.07278, 6);

        expect(mutualInfo([0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 1, 1, 0, 0, 0, 1, 1, 1])).toBeCloseTo(0, 6);

        expect(mutualInfo([1, 1, 1, 1, 0, 0, 0, 0, 1], [1, 1, 1, 0, 0, 0, 1, 1, 1])).toBeCloseTo(0.07278, 6);

        expect(mutualInfo([1, 1, 0, 0, 1, 1, 0, 0, 1], [1, 1, 1, 0, 0, 0, 1, 1, 1])).toBeCloseTo(0.018311, 6);

        expect(mutualInfo([0, 1, 0, 1, 0, 1, 0, 1], [0, 2, 0, 2, 0, 2, 0, 2])).toBeCloseTo(1.0, 6);

        expect(mutualInfo([0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1], [0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2])).toBeCloseTo(
            0.666667,
            6,
        );

        expect(mutualInfo([0, 0, 1, 1, 2, 1, 1, 0, 0], [0, 0, 0, 1, 1, 1, 0, 0, 0])).toBeCloseTo(0.473851, 6);

        expect(mutualInfo([0, 1, 0, 0, 1, 0, 0, 1, 0], [1, 0, 0, 1, 0, 0, 1, 0, 0])).toBeCloseTo(0.251629, 6);

        expect(mutualInfo([1, 0, 0, 1, 0, 0, 1, 0], [2, 0, 1, 2, 0, 1, 2, 0])).toBeCloseTo(0.954434, 6);
    });
});
