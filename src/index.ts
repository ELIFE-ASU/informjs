const informcpp = require('../build/Release/informcpp');

export function add(a: number, b: number): number {
    return informcpp.add(a, b);
}
