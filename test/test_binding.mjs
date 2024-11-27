import {create, destroy} from "../lib/binding.js";

// needs jest tests with real window creation
try {
  create(123, 'test')
  destroy(123)
} catch (err) {
  console.error(err)
}
