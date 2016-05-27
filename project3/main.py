print("test")

def parse_data(data):
	parsed_data = []
	for line in data:
		parsed = line.translate(None, '()".\'!?+-=\\:/_;')
		#parsed = parsed.translate(None, ')')
		parsed = parsed.split(',')
		parsed_data.append(parsed)
	return parsed_data

def create_vocab(data):
	vocab = []
	for sentence in data:
		words = sentence[0].split(' ')	
		for word in words:
			#hanlde base case
			if not vocab:
				vocab.append([word,1])
			
			added = False
			for value in vocab:
				if word in value:
					value[1] += 1
					added = True

			if added == False:
				vocab.append([word,1])
	print vocab
	#print(words)

def main():
	#Read in the test data
	test = open("training_text.txt").read().splitlines()
	data = parse_data(test)
	vocab = create_vocab(data)
	#print(data)

main()
