const informcpp = require('../build/Release/informcpp');

export type Series = number[] | Int32Array | ArrayBuffer;

export function mutualInfo(xs: Series, ys: Series): number {
    return informcpp.mutualInfo(xs, ys);
}

export function transferEntropy(source: Series, target: Series, k: number): number {
    return informcpp.transferEntropy(source, target, k);
}
