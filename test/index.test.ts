import * as inform from '../src';

describe('check exports', () => {
    test('.has mutualInfo', () => expect(inform.mutualInfo).toBeDefined());
});
