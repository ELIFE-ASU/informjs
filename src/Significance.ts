import * as seedrandom from 'seedrandom';
import * as Core from './Core';
import { Series } from './Core';

/**
 * An RNG to use by default. This global allows us to avoid recreating
 * the RNG every time an RNG is needed, but not provided.
 */
const localRNG = seedrandom();

/**
 * The required interface for a random number generator (RNG).
 *
 * Note that [seedrandom's](https://npmjs.org/package/seedrandom) `prng`
 * satistifies this interface.
 */
export interface RNG {
    /**
     * Return a random number in the range $[0,1)$.
     */
    double(): number;
}

/**
 * The statistical significance of a computed value.
 */
export interface Sig {
    /**
     * A two-sided p-value
     */
    p: number;
    /**
     * The standard error for the p-value
     */
    se: number;
}

/**
 * A computed value with statistical significance.
 */
export interface SigValue {
    /**
     * The computed value
     */
    value: number;
    /**
     * The statistical significance of that value
     */
    sig: Sig;
}

/**
 * Randomly shuffle an `Int32Array` in place using
 * Durstenfeld's version of the [Fisher-Yates
 * shuffle](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm).
 */
function shuffleInPlace(series: Int32Array, rng?: RNG): Int32Array {
    if (rng === undefined) {
        rng = localRNG;
    }

    let currentIndex = series.length;
    let temporaryValue;
    let randomIndex;
    while (currentIndex !== 0) {
        randomIndex = Math.floor(rng.double() * currentIndex);
        currentIndex -= 1;
        temporaryValue = series[currentIndex];
        series[currentIndex] = series[randomIndex];
        series[randomIndex] = temporaryValue;
    }
    return series;
}

/**
 * Computes the mutual information between two time series, together
 * with statistical significance. To compute the significance, we use
 * a permutation test with `nperm` permutations.
 *
 * @param xs     observations of the first variable
 * @param ys     observations of the second variable
 * @param nperm  number of permutations
 * @param rng    a random number generator
 * @returns      the computed mutual information and estimated statistical significance
 *
 * @see [`informjs.mutualInfo`](_core_.html#mutualinfo)
 *
 * # Examples:
 *
 * ```typescript
 * import { Significance } from 'inform';
 * import * as seedrandom from 'seedrandom';
 *
 * const { mutualInfo } = Significance;
 *
 * const xs = [0,0,1,1,2,1,1,0,0];
 * const ys = [0,0,0,1,1,1,0,0,0];
 *
 * mutualInfo(xs, ys, 100000); // Uses a default RNG, automatically seeded
 * // value will always be the same, but sig will vary based on the seed.
 * //
 * // {
 * //   value: 0.47385138961004514,
 * //   sig: { p: 0.16682833171668282, se: 0.0011789683602765229 }
 * // }
 *
 * mutualInfo(xs, ys, 100000, seedrandom('2019'));
 * // Should deterministically yield:
 * //
 * // {
 * //   value: 0.47385138961004514,
 * //   sig: { p: 0.16682833171668282, se: 0.0011789683602765229 }
 * // }
 * ```
 */
export function mutualInfo(xs: Series, ys: Series, nperm: number, rng?: RNG): SigValue {
    if (nperm < 10) {
        throw new TypeError(`too few permutations; got ${nperm} < 10`);
    }

    const as = new Int32Array(xs.slice(0));
    const bs = new Int32Array(ys.slice(0));

    const mi = Core.mutualInfo(as, bs);
    let count = 1;
    for (let i = 0; i < nperm; ++i) {
        count += Number(Core.mutualInfo(as, shuffleInPlace(bs, rng)) >= mi);
    }
    const p = count / (nperm + 1);
    const se = Math.sqrt((p * (1 - p)) / (nperm + 1));
    return { value: mi, sig: { p, se } };
}

/**
 * Computes the active information of a time series, together with statistical
 * significance. To compute the significance, we use a permutation test with
 * `nperm` permutations.
 *
 * @param xs     observations of the first variable
 * @param k      the history length ($k \geq 1$)
 * @param nperm  number of permutations
 * @param rng    a random number generator
 * @returns      the computed active information and estimated statistical significance
 *
 * @see [`informjs.activeInfo`](_core_.html#activeInfo)
 *
 * # Examples:
 *
 * ```typescript
 * import { Significance } from 'inform';
 * import * as seedrandom from 'seedrandom';
 *
 * const { activeInfo } = Significance;
 *
 * const xs = [0,0,1,1,2,1,1,0,0];
 *
 * activeInfo(xs, 2, 100000); // Uses a default RNG, automatically seeded
 * // value will always be the same, but sig will vary based on the seed.
 * //
 * // {
 * //   value: 1.0930692077718898,
 * //   sig: { p: 0.33747662523374766, se: 0.0014952722722481686 }
 * // }
 *
 * activeInfo(xs, 2, 100000, seedrandom('2019'));
 * // Should deterministically yield:
 * //
 * // {
 * //   value: 1.0930692077718898,
 * //   sig: { p: 0.33684663153368466, se: 0.0014945860449323385 }
 * // }
 * ```
 */
export function activeInfo(xs: Series, k: number, nperm: number, rng?: RNG): SigValue {
    if (nperm < 10) {
        throw new TypeError(`too few permutations; got ${nperm} < 10`);
    }

    const as = new Int32Array(xs.slice(0));

    const ai = Core.activeInfo(as, k);
    let count = 1;
    for (let i = 0; i < nperm; ++i) {
        count += Number(Core.activeInfo(shuffleInPlace(as, rng), k) >= ai);
    }
    const p = count / (nperm + 1);
    const se = Math.sqrt((p * (1 - p)) / (nperm + 1));
    return { value: ai, sig: { p, se } };
}

/**
 * Computes the transfer entropy between two time series, together
 * with statistical significance. To compute the significance, we use
 * a permutation test with `nperm` permutations.
 *
 * @param source  observations of the source variable
 * @param target  observations of the target variable
 * @param k       the history length ($k \geq 1$)
 * @param nperm   number of permutations
 * @param rng     a random number generator
 * @returns       the computed transfer entropy and estimated statistical significance
 *
 * @see [`informjs.transferEntropy`](_core_.html#transferentropy)
 *
 * # Examples:
 *
 * ```typescript
 * import { Significance } from 'inform';
 * import * as seedrandom from 'seedrandom';
 *
 * const { transferEntropy } = Significance;
 *
 * const xs = [0,0,1,1,2,1,1,0,0];
 * const ys = [0,0,0,1,1,1,0,0,0];
 *
 * transferEntropy(xs, ys, 2, 100000); // Uses a default RNG, automatically seeded
 * // value will always be the same, but sig will vary based on the seed.
 * //
 * // {
 * //   value: 0.6792696431662097,
 * //   sig: { p: 0.2824871751282487, se: 0.0014236859591086474 }
 * // }
 *
 * transferEntropy(xs, ys, 2, 100000, seedrandom('2019'));
 * // Should deterministically yield:
 * //
 * // {
 * //   value: 0.6792696431662097,
 * //   sig: { p: 0.27848721512784874, se: 0.0014175051539172055 }
 * // }
 * ```
 */
export function transferEntropy(source: Series, target: Series, k: number, nperm: number, rng?: RNG): SigValue {
    if (nperm < 10) {
        throw new TypeError(`too few permutations; got ${nperm} < 10`);
    }
    const ss = new Int32Array(source.slice(0));
    const ts = new Int32Array(target.slice(0));

    const te = Core.transferEntropy(ss, ts, k);
    let count = 1;
    for (let i = 0; i < nperm; ++i) {
        count += Number(Core.transferEntropy(shuffleInPlace(ss, rng), ts, k) >= te);
    }
    const p = count / (nperm + 1);
    const se = Math.sqrt((p * (1 - p)) / (nperm + 1));
    return { value: te, sig: { p, se } };
}
