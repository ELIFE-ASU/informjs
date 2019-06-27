const informcpp = require('../build/Release/informcpp');

/**
 * The current implementation only supports 1-dimension time series of
 * integer values. This is represented with the `Series` type. If the
 * contents of a `Series` variable is invalid, a `TypeError` is raised.
 */
export type Series = number[] | Int32Array | ArrayBuffer;

/**
 * [Mutual information](https://en.wikipedia.org/wiki/Mutual_information)
 * (MI) is a measure of mutual dependence between at least
 * two random variables, though only the bivariate form is
 * currently implemented in **informjs**. There are a number of
 * different definitions of mutual information for more than two
 * variables. [Inform](https://elife-asu.github.io/Inform) implements
 * it as
 *
 * $$
 *    I(X_1, \ldots, X_l) = \sum_{x_{1,i}, \ldots, x_{l,i}} p(x_{1,i}, \ldots, x_{l,i})
 *        \frac{p(x_{1,i}, \ldots, x_{l,i})}{p(x_{1,i}) \ldots p(x_{l,i})}
 * $$
 *
 * See [Cover1991] for more details.
 *
 * @param xs  observations of first variable
 * @param ys  observations of second variable
 * @returns   the mutual information between the variables
 *
 * # Examples
 *
 * ```javascript
 * > xs = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1];
 * > ys = [0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1];
 * > mutualInfo(xs, ys)
 * 0.21417094500762912
 * ```
 *
 * # References
 * [Cover1991] Cover, T.M. and Thomas, J.A. (1991) "Elements of information theory". New York: Wiley. ISBN
 * 0-471-06259-6.
 */
export function mutualInfo(xs: Series, ys: Series): number {
    return informcpp.mutualInfo(xs, ys);
}

/**
 * Transfer entropy (TE) was introduced by [Schreiber2000]() to quantify
 * information transfer between an information source and target,
 * conditioning out shared history effects. This implementation allows the
 * user to provide source $X$ and target $Y$ time series and a history
 * length $k$. The transfer entropy is then essentially the conditional
 * mutual information between $X$ and $Y$, conditioned on the length-$k$
 * history of $Y$:
 * $$
 *   T_{X \rightarrow Y}(k) = \sum_{y_{i+1}, y^{(k)}, x_i} p(y_{i+1}, y^{(k)}, x_i)
 *       \log_2{\frac{p(y_{i+1}, x_i ~|~ y^{(k)})}{p(y_{i+1} ~|~ y^{(k)})p(x_i ~|~ y^{(k)})}}
 * $$
 *
 * @param source  observations of the source variable
 * @param target  observations of the target variable
 * @param k       the history length ($k \geq 1$)
 * @returns       the transfer entropy between the variables
 *
 * # Examples:
 * ```javascript
 * > xs = [0,1,1,1,1,0,0,0,0]
 * > ys = [0,0,1,1,1,1,0,0,0]
 * > transferEntropy(xs, ys, 2)
 * 0.6792696431662097
 * ```
 *
 * # References:
 *
 * [Schreiber2000] Shreiber, T. (2000) "[Measuring information
 * transfer](https://dx.doi.org/10.1103/PhysRevLett.85.461)". _Physical Review Letters_. **85** (2):
 * 461-464. doi:10.1103/PhysRevLett.85.461
 */
export function transferEntropy(source: Series, target: Series, k: number): number {
    return informcpp.transferEntropy(source, target, k);
}
