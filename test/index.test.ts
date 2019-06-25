import * as inform from '../src';

describe('check exports', () => {
    test('.has add', () => expect(inform.add).toBeDefined());
});

describe('add', () => {
    test('.can add', () => expect(inform.add(2, 3)).toBe(5));
});
