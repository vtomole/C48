(in-package :eval)

(defun repl ()
  (format t "~%repl>") 
  (print (eval (string (read-line))))
  (repl))

