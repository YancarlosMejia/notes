$(TARGET)_3_65.out: $(TARGET).bc
	../pipair $< >$@ 2>test_3_65.err

$(TARGET)_10_80.out: $(TARGET).bc
	../pipair $< 10 80 >$@ 2>test_10_80.err

outputs: $(TARGET)_3_65.out $(TARGET)_10_80.out
