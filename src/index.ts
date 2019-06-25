const informcpp = require('../build/Release/informcpp');

export function mutualInfo(xs: number[], ys: number[]): number {
    return informcpp.mutualInfo(xs, ys);
}
