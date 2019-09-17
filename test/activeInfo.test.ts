import { activeInfo } from '../src';

describe('active information', () => {
    test('.throws for empty', () => {
        expect(() => activeInfo([], 2)).toThrow(/NULL/);
    });

    test.each`
        xs                                   | message
        ${[-1, 0, 0]}                        | ${'negative'}
        ${new Int32Array([-1, 0, 0])}        | ${'negative'}
        ${new Int32Array([-1, 0, 0]).buffer} | ${'negative'}
        ${[0.5, 0, 0]}                       | ${'not an integer'}
    `('.invalid element', ({ xs, message }) => {
        expect(() => activeInfo(xs, 2)).toThrow(message);
    });

    test('.invalid buffer length', () => {
        const xs = new Int8Array([1, 0, 1]).buffer;
        expect(() => activeInfo(xs, 2)).toThrow(/inconsistent/);
    });

    test('.invalid history length', () => {
        expect(() => activeInfo([0, 0, 0], -1)).toThrow(/history length/);
        expect(() => activeInfo([0, 0, 0], 0)).toThrow(/history length/);
        expect(() => activeInfo([0, 0, 0], 0.5)).toThrow(/history length/);

        expect(() => activeInfo([0, 0], 2)).toThrow(/history length/);
        expect(() => activeInfo([0, 0], 3)).toThrow(/history length/);
        expect(() => activeInfo([0, 0, 0, 0], 4)).toThrow(/history length/);
        expect(() => activeInfo([0, 0, 0, 0], 5)).toThrow(/history length/);
    });

    test('.all array types supported', () => {
        const xs = [1, 1, 0, 0, 1];

        const xsInt32 = new Int32Array(xs);
        const xsBuffer = xsInt32.buffer;

        const expected = 0.918296;

        expect(activeInfo(xs, 2)).toBeCloseTo(expected, 6);
        expect(activeInfo(xsInt32, 2)).toBeCloseTo(expected, 6);
        expect(activeInfo(xsBuffer, 2)).toBeCloseTo(expected, 6);
    });

    test.each`
        xs                             | k    | ai
        ${[1, 1, 0, 0, 1, 0, 0, 1]}    | ${2} | ${0.918296}
        ${[1, 1, 0, 0, 1, 0, 0, 1]}    | ${3} | ${0.970951}
        ${[1, 0, 0, 0, 0, 0, 0, 0, 0]} | ${2} | ${0.0}
        ${[1, 0, 0, 0, 0, 0, 0, 0, 0]} | ${3} | ${0.0}
        ${[0, 0, 1, 1, 1, 1, 0, 0, 0]} | ${2} | ${0.305958}
        ${[0, 0, 1, 1, 1, 1, 0, 0, 0]} | ${3} | ${0.666667}
        ${[1, 0, 0, 0, 0, 0, 0, 1, 1]} | ${2} | ${0.347458}
        ${[1, 0, 0, 0, 0, 0, 0, 1, 1]} | ${3} | ${0.377444}
        ${[0, 0, 0, 0, 0, 1, 1, 0, 0]} | ${2} | ${0.399533}
        ${[0, 0, 0, 0, 0, 1, 1, 0, 0]} | ${3} | ${0.459148}
        ${[0, 0, 0, 0, 1, 1, 0, 0, 0]} | ${2} | ${0.399533}
        ${[0, 0, 0, 0, 1, 1, 0, 0, 0]} | ${3} | ${0.584963}
        ${[1, 1, 1, 0, 0, 0, 0, 1, 1]} | ${2} | ${0.305958}
        ${[1, 1, 1, 0, 0, 0, 0, 1, 1]} | ${3} | ${0.584963}
        ${[3, 3, 3, 2, 1, 0, 0, 0, 1]} | ${2} | ${1.270942}
        ${[3, 3, 3, 2, 1, 0, 0, 0, 1]} | ${3} | ${1.459148}
        ${[2, 2, 3, 3, 3, 3, 2, 1, 0]} | ${2} | ${1.270942}
        ${[2, 2, 3, 3, 3, 3, 2, 1, 0]} | ${3} | ${1.459148}
        ${[2, 2, 2, 2, 2, 2, 1, 1, 1]} | ${2} | ${0.469565}
        ${[2, 2, 2, 2, 2, 2, 1, 1, 1]} | ${3} | ${0.459148}
    `('.can', ({ xs, k, ai }) => {
        expect(activeInfo(xs, k)).toBeCloseTo(ai, 6);
    });
});
