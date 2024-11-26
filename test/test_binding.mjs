import {create, destroy} from "../lib/binding.js";

try {
  create(123, 'test')
  destroy(123)
} catch (err) {
  console.error(err)
}
