--- srm_oparray.c	2020-09-20 16:36:58.281375025 +0800
+++ srm_oparray_modify.c	2020-09-20 16:36:25.000000000 +0800
@@ -635,9 +635,9 @@ void vld_dump_op(int nr, zend_op * op_pt
 	unsigned int flags, op1_type, op2_type, res_type;
 	const zend_op op = op_ptr[nr];
 
- 	if (op.lineno == 0) {
- 		return;
- 	}
+// 	if (op.lineno == 0) {
+// 		return;
+// 	}
 
 	if (op.opcode >= NUM_KNOWN_OPCODES) {
 		flags = ALL_USED;
