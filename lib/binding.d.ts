/**
 * @param {Buffer | number} hwnd
 * @param {string} reason
 */
export function create(hwnd: Buffer | number, reason: string): void;
/**
 * @param {Buffer | number} hwnd
 */
export function destroy(hwnd: Buffer | number): void;
