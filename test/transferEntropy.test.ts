import { transferEntropy } from '../src';

describe('transfer entropy', () => {
    test('.throws for different lengths', () => {
        expect(() => transferEntropy([0, 0, 0], [0, 0, 0, 0], 2)).toThrow(/different lengths/);
        expect(() => transferEntropy([0, 0, 0, 0], [0, 0, 0], 2)).toThrow(/different lengths/);
    });

    test('.throws for empty', () => {
        expect(() => transferEntropy([], [], 2)).toThrow(/NULL/);
    });

    test.each`
        xs                                   | ys                                   | message
        ${[-1, 0, 0]}                        | ${[1, 1, 0]}                         | ${'negative'}
        ${[1, 0, 0]}                         | ${[-1, 1, 0]}                        | ${'negative'}
        ${new Int32Array([-1, 0, 0])}        | ${new Int32Array([1, 1, 0])}         | ${'negative'}
        ${new Int32Array([1, 0, 0])}         | ${new Int32Array([-1, 1, 0])}        | ${'negative'}
        ${new Int32Array([-1, 0, 0]).buffer} | ${new Int32Array([1, 1, 0]).buffer}  | ${'negative'}
        ${new Int32Array([1, 0, 0]).buffer}  | ${new Int32Array([-1, 1, 0]).buffer} | ${'negative'}
        ${[0.5, 0, 0]}                       | ${[1, 1, 0]}                         | ${'not an integer'}
        ${[0, 0, 0]}                         | ${[0.5, 1, 0]}                       | ${'not an integer'}
    `('.invalid element', ({ xs, ys, message }) => {
        expect(() => transferEntropy(xs, ys, 2)).toThrow(message);
    });

    test('.invalid buffer length', () => {
        const xs = new Int8Array([0, 0, 0]).buffer;
        const ys = new Int8Array([1, 0, 1]).buffer;
        expect(() => transferEntropy(xs, ys, 2)).toThrow(/inconsistent/);
    });

    test('.invalid history length', () => {
        expect(() => transferEntropy([0, 0, 0], [0, 0, 0], -1)).toThrow(/history length/);
        expect(() => transferEntropy([0, 0, 0], [0, 0, 0], 0)).toThrow(/history length/);
        expect(() => transferEntropy([0, 0, 0], [0, 0, 0], 0.5)).toThrow(/history length/);

        expect(() => transferEntropy([0, 0], [0, 0], 3)).toThrow(/history length/);
        expect(() => transferEntropy([0, 0, 0, 0], [0, 0, 0, 0], 5)).toThrow(/history length/);
    });

    test('.all array types supported', () => {
        const xs = [1, 1, 0, 0, 1];
        const ys = [1, 1, 1, 0, 0];

        const xsInt32 = new Int32Array(xs);
        const ysInt32 = new Int32Array(ys);
        const xsBuffer = xsInt32.buffer;
        const ysBuffer = ysInt32.buffer;

        expect(transferEntropy(xs, ys, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xs, ysInt32, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xs, ysBuffer, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xsInt32, ys, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xsInt32, ysInt32, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xsInt32, ysBuffer, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xsBuffer, ys, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xsBuffer, ysInt32, 2)).toBeCloseTo(0.666667, 6);
        expect(transferEntropy(xsBuffer, ysBuffer, 2)).toBeCloseTo(0.666667, 6);
    });

    test.each`
        xs                                | ys                                | a      | b           | c       | d
        ${[1, 1, 1, 0, 0]}                | ${[1, 1, 0, 0, 1]}                | ${0.0} | ${0.666667} | ${0.0}  | ${0.0}
        ${[0, 1, 0, 1, 0, 0, 1, 1, 0, 0]} | ${[0, 0, 1, 0, 1, 1, 1, 0, 1, 1]} | ${0.0} | ${0.344361} | ${0.25} | ${0.0}
    `('.can', ({ xs, ys, a, b, c, d }) => {
        expect(transferEntropy(xs, xs, 2)).toBeCloseTo(a, 6);
        expect(transferEntropy(ys, xs, 2)).toBeCloseTo(b, 6);
        expect(transferEntropy(xs, ys, 2)).toBeCloseTo(c, 6);
        expect(transferEntropy(ys, ys, 2)).toBeCloseTo(d, 6);
    });
});
