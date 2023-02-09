import PyPDF2
import string

pdf_file = open("C:/Users/saksh/Downloads/King-Lear-PDF.pdf",'rb')
pdf_reader = PyPDF2.PdfFileReader(pdf_file)
punctuation = string.punctuation
for page_number in range(pdf_reader.numPages):
    page = pdf_reader.getPage(page_number)
    page_text = page.extractText()
    filtered_text = "".join([char for char in page_text if char not in punctuation])
    with open(f"{page_number + 1}.txt", 'w') as text_file:
        text_file.write(filtered_text)
pdf_file.close()
pdf_file.close()
