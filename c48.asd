(asdf:defsystem #:c48
    :description "Lisp system definition for c48"
    :author "Victory Omole"
    :license "MIT"
    :depends-on (#:cffi)
    :serial t
    :components ((:file "src/package")
		 (:file "src/eval")
		 (:file "src/repl")))
