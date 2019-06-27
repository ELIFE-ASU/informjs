import * as informjs from '../src';

describe('check exports', () => {
    test('.has mutualInfo', () => expect(informjs.mutualInfo).toBeDefined());
    test('.has transferEntropy', () => expect(informjs.transferEntropy).toBeDefined());
	test('.has Significance', () => expect(informjs.Significance).toBeDefined());
});
