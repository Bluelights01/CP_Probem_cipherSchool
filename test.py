def validate_test_file(filename):
    with open(filename, 'r') as f:
        # Read lines and remove extra whitespace/empty lines at the end
        lines = [line.strip() for line in f if line.strip()]
    
    # Check if the total number of lines is a multiple of 3
    if len(lines) % 3 != 0:
        print(f"❌ Error: File has {len(lines)} lines. It must be a multiple of 3.")
        return False

    # Iterate through the file in chunks of 3
    for i in range(0, len(lines), 3):
        block_num = (i // 3) + 1
        n_str, text, k_str = lines[i:i+3]

        try:
            n = int(n_str)
            k = int(k_str)
            
            # Logic Check: Does string length match n? 
            # (Remove this 'if' if your format allows different lengths)
            if len(text) != n:
                print(f"⚠️ Block {block_num}: String length ({len(text)}) does not match n ({n})")
                return False
                
        except ValueError:
            print(f"❌ Block {block_num}: Format Error. 'n' or 'k' are not integers.")
            return False

    print("✅ File format is correct!")
    return True

# To run it:
validate_test_file('hidden_test.txt')