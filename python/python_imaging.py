import numpy
import yarp
import scipy.ndimage
import matplotlib.pylab

# Initialise YARP
yarp.Network.init()


def python_to_yarp():
	# Create the array with random data
	img_array = numpy.random.uniform(0., 255., (240, 320)).astype(numpy.float32)

	# Create the yarp image and wrap it around the array  
	yarp_image = yarp.ImageFloat()
	yarp_image.setExternal(img_array, img_array.shape[1], img_array.shape[0])
	
	# Alternatively, if using Python 2.x, try:
	# yarp_image.setExternal(img_array.__array_interface__['data'][0], img_array.shape[1], img_array.shape[0])

	# Create the yarp port, connect it to the running instance of yarpview and send the image
	output_port = yarp.Port()
	output_port.open("/python-image-port")
	yarp.Network.connect("/python-image-port", "/view01")
	output_port.write(yarp_image)

	# Cleanup
	output_port.close()


def yarp_to_python():
	# Create a port and connect it to the iCub simulator virtual camera
	input_port = yarp.Port()
	input_port.open("/python-image-port")
	yarp.Network.connect("/icubSim/cam", "/python-image-port")

	# Create numpy array to receive the image and the YARP image wrapped around it
	img_array = numpy.zeros((240, 320, 3), dtype=numpy.uint8)
	yarp_image = yarp.ImageRgb()
	yarp_image.resize(320, 240)
	yarp_image.setExternal(img_array, img_array.shape[1], img_array.shape[0])
	
	# Alternatively, if using Python 2.x, try:
	# yarp_image.setExternal(img_array.__array_interface__['data'][0], img_array.shape[1], img_array.shape[0])

	# Read the data from the port into the image
	input_port.read(yarp_image)

	# display the image that has been read
	matplotlib.pylab.imshow(img_array)

	# Cleanup
	input_port.close()


class SobelFilter:
	"""Object that reads an image from a port, transforms it and sends the result to another port.
	
	The object reads RGB images and sends monochrome ones with calculated sobel filter.
	Note: this class uses the alternative implementation of setExternal together with numpy array interface.
	"""
	
	def __init__(self, input_port_name, output_port_name):		
		# Prepare ports
		self._input_port = yarp.Port()
		self._input_port_name = input_port_name
		self._input_port.open(self._input_port_name)

		self._output_port = yarp.Port()
		self._output_port_name = output_port_name
		self._output_port.open(self._output_port_name)
				
		# Prepare image buffers
		# Input
		self._input_buf_image = yarp.ImageRgb()
		self._input_buf_image.resize(320, 240)
		self._input_buf_array = numpy.zeros((240, 320, 3), dtype = numpy.uint8)
		self._input_buf_image.setExternal(self._input_buf_array.__array_interface__['data'][0], self._input_buf_array.shape[1], self._input_buf_array.shape[0])
		# Output
		self._output_buf_image = yarp.ImageFloat()
		self._output_buf_image.resize(320, 240)
		self._output_buf_array = numpy.zeros((240, 320), dtype = numpy.float32)
		self._output_buf_image.setExternal(self._output_buf_array.__array_interface__['data'][0], self._output_buf_array.shape[1], self._output_buf_array.shape[0])
		
	def run(self):	
		while True: # Break this by hitting CTRL-C
			# Read an image from the port
			self._input_port.read(self._input_buf_image)
			
			# Make sure the image has not been re-allocated
			assert self._input_buf_array.__array_interface__['data'][0] == self._input_buf_image.getRawImage().__long__()
			
			# Let's calculate the sobel filter
			self._output_buf_array[:,:] = scipy.ndimage.filters.sobel(self._input_buf_array.mean(2) / 255.)
			# Normalise the result
			self._output_buf_array -= self._output_buf_array.min()
			self._output_buf_array /= self._output_buf_array.max()
			self._output_buf_array *= 255.
			
			# Send the result to the output port
			self._output_port.write(self._output_buf_image)
			
	def cleanup(self):
		self._input_port.close()
		self._output_port.close()


if __name__=="__main__":
	# Example demonstrating how to use the SobelFilter class implemented above
	# This assumes iCub simulator is running with world camera at /icubSim/cam
	# and an instance of yarpview with port name /view01
	
	image_filter = SobelFilter("/sobel:in", "/sobel:out")
	
	try:
		assert yarp.Network.connect("/sobel:out", "/view01")
		assert yarp.Network.connect("/icubSim/cam", "/sobel:in")
		
		image_filter.run()
	finally:
		image_filter.cleanup()
