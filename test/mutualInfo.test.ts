import { mutualInfo } from '../src';

describe('mutual information', () => {
    test('.throws for different lengths', () => {
        expect(() => mutualInfo([], [0])).toThrow(/different lengths/);
        expect(() => mutualInfo([0], [])).toThrow(/different lengths/);
    });

    test('.throws for empty', () => {
        expect(() => mutualInfo([], [])).toThrow(/NULL/);
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
        expect(() => mutualInfo(xs, ys)).toThrow(message);
    });

    test('.invalid buffer length', () => {
        const xs = new Int8Array([0, 0, 0]).buffer;
        const ys = new Int8Array([1, 0, 1]).buffer;
        expect(() => mutualInfo(xs, ys)).toThrow(/inconsistent/);
    });

    test.each`
        xs                                      | ys                                      | mi
        ${[0, 0, 0, 0, 1, 1, 1, 1]}             | ${[1, 1, 1, 1, 0, 0, 0, 0]}             | ${1.0}
        ${[0, 1, 0, 1, 0, 1, 0, 1]}             | ${[0, 2, 0, 2, 0, 2, 0, 2]}             | ${1.0}
        ${[1, 0, 0, 1, 0, 0, 1, 0]}             | ${[2, 0, 1, 2, 0, 1, 2, 0]}             | ${0.954434}
        ${[0, 0, 1, 1, 1, 1, 0, 0, 0]}          | ${[1, 1, 0, 0, 0, 0, 1, 1, 1]}          | ${0.991076}
        ${[1, 1, 0, 1, 0, 1, 1, 1, 0]}          | ${[1, 1, 0, 0, 0, 1, 0, 1, 1]}          | ${0.07278}
        ${[0, 0, 0, 0, 0, 0, 0, 0, 0]}          | ${[1, 1, 1, 0, 0, 0, 1, 1, 1]}          | ${0.0}
        ${[1, 1, 1, 1, 0, 0, 0, 0, 1]}          | ${[1, 1, 1, 0, 0, 0, 1, 1, 1]}          | ${0.07278}
        ${[1, 1, 0, 0, 1, 1, 0, 0, 1]}          | ${[1, 1, 1, 0, 0, 0, 1, 1, 1]}          | ${0.018311}
        ${[0, 0, 1, 1, 2, 1, 1, 0, 0]}          | ${[0, 0, 0, 1, 1, 1, 0, 0, 0]}          | ${0.473851}
        ${[0, 1, 0, 0, 1, 0, 0, 1, 0]}          | ${[1, 0, 0, 1, 0, 0, 1, 0, 0]}          | ${0.251629}
        ${[0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]} | ${[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2]} | ${0.666667}
    `('.can', ({ xs, ys, mi }) => {
        const xsInt32 = new Int32Array(xs);
        const ysInt32 = new Int32Array(ys);
        const xsBuffer = xsInt32.buffer;
        const ysBuffer = ysInt32.buffer;

        expect(mutualInfo(xs, ys)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xs, ysInt32)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xs, ysBuffer)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xsInt32, ys)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xsInt32, ysInt32)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xsInt32, ysBuffer)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xsBuffer, ys)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xsBuffer, ysInt32)).toBeCloseTo(mi, 6);
        expect(mutualInfo(xsBuffer, ysBuffer)).toBeCloseTo(mi, 6);
    });
});
