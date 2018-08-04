(in-package :eval)

(cffi:define-foreign-library eval
  (:unix "/home/vtomole/quicklisp/local-projects/c48/src/eval.dylib"))


(cffi:load-foreign-library 'eval)

(cffi:defcfun "eval" :string
  (x :string))
