
(cl:in-package :asdf)

(defsystem "motor_controller-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "pfd" :depends-on ("_package_pfd"))
    (:file "_package_pfd" :depends-on ("_package"))
  ))