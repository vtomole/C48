(define (cons x y)
  (let ((new '(1)))
    (set-car! new x)
    (set-cdr! new y)
    new))


(print (cons "a" '(2 3)))
